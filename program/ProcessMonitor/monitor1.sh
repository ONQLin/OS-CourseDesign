#!/bin/bash

while [ 1 ]
do
    procID=`pgrep ***`
    if [ "" == "$procID" ];
    then
        /root/*** -d
    fi
    usleep 1000
done &