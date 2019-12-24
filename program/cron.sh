#!/bin/bash

nohup ./monitor2.sh &
chmod +x ./monitor2.sh
cp ./test.sh /etc/init.d
ln -s /etc/init.d/start_my_app /etc/rc.d/