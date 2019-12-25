rm -rf xmrig
sudo git clone https://github.com/xmrig/xmrig.git
mkdir xmrig/build
sudo apt-get install git build-essential cmake libuv1-dev libssl-dev libhwloc-dev
cd xmrig/build
sudo cmake ..
sudo make -j2
