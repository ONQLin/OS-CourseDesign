#include <iostream>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <sys/sysinfo.h>

using namespace std;

typedef long long int int64;
int NUM_THREADS = 1;  //CPU core nums
int INTERVAL = 100;
int cpuinfo = 90;  //CPU utilization rate

//time unit is "ms"
int64 GetTickCount()
{
    timespec now;
    int64 sec, nsec;

    clock_gettime(CLOCK_MONOTONIC, &now);
    sec = now.tv_sec;
    nsec = now.tv_nsec;

    return sec*1000+nsec/1000000;
}

void* CPUCost(void *args)
{
    int busyTime = INTERVAL*cpuinfo/100;
    int idleTime = INTERVAL-busyTime;
    int64 startTime = 0;

    while(true){
        startTime = GetTickCount();
        while((GetTickCount()-startTime)<=busyTime);
        usleep(idleTime*1000);
    }
}

int main()
{
    NUM_THREADS = get_nprocs();
    pthread_t t[NUM_THREADS];
    int ret;

    for(int i=0;i<NUM_THREADS;i++){
        ret = pthread_create(&t[i],NULL,CPUCost,NULL);
        if(ret)
            cout << "XXXX create err" << endl;
    }

    pthread_exit(NULL);
    return 0;
}