#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h> 
#include<stdio.h> 
#include<stdlib.h> 
#include<fcntl.h> 
#include<limits.h> 

#define BUFSZ PIPE_BUF 

int init_daemon(void) 
{ 
	int pid; 
	int i; 
 
	signal(SIGTTOU,SIG_IGN);    //ignore terminal
	signal(SIGTTIN,SIG_IGN);
	signal(SIGTSTP,SIG_IGN);
	signal(SIGHUP,SIG_IGN);
	
	pid = fork();
	if(pid > 0) {
		exit(0); // to daemon
	}
	else if(pid < 0) { 
		return -1;
	}
	//become the first process
	setsid();
	pid=fork();
	if( pid > 0) {
		exit(0);
	}
	else if( pid< 0) {
		return -1;
	}
	for(i=0;i< NOFILE;close(i++));
	chdir("/");
	umask(0);
	signal(SIGCHLD,SIG_IGN); 
	return 0;

void err_quit(char *msg)     //msg for debug       
{ 
perror(msg); 
exit(EXIT_FAILURE); 
} 

int main(int argc, char *argv[])     //user mode
{ 
init_daemon();
FILE* fps; 
int count; 
char buf[BUFSZ]; 
char command[150]; 
if(argc != 2) 
{
printf("USAGE: example <process name>\n"); //......
exit(EXIT_SUCCESS); 
} 
else
sprintf(command, "ps -C %s|wc -l", argv[1] );       //ask the ps   %s|wc is decided by the process name

if((fps = popen(command,"r")) == NULL)               // ps——>file*
err_quit("popen"); 
while(1)
    if( (fgets(buf,BUFSZ,fps))!= NULL) 
    {
        count = atoi(buf); 
        if((count - 1) == 0){
            printf("%s not found\n",argv[1]);

        }
        else{
            printf("process : %s total is %d\n",argv[1],(count - 1)); 

        }
    } 
}
pclose(fps); 
exit(EXIT_SUCCESS); 
} 