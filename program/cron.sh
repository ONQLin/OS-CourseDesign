#!/bin/bash
cp monitor.sh /etc/init.d/
cd /etc/init.d
chmod 755 /etc/init.d/test.sh
update-rc.d test.sh defaults
cd /home

./monitor.sh >/dev/null 2>&1 &