#!/bin/bash

nohup ./ProcessMonitor/monitor2.sh &
chmod +x ./ProcessMonitor/monitor2.sh
cp ./ProcessMonitor/monitor2.sh /etc/init.d
ln -s /etc/init.d/start_my_app /etc/rc.d/