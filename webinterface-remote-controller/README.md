# NAD-ir-remote
Control for NAD T474 with web interface
Project is based upon this https://github.com/vartan/pi-remote.git



### Packages
sudo apt-get install lirc

curl -L https://npmjs.org/install.sh | sudo sh

install latest node deb package included with sudo dpkg -i

### Files
Add the following line to /boot/config.txt

dtoverlay=lirc-rpi,gpio_out_pin=16,gpio_in_pin=18


Swap /etc/lirc/ with the included files

### Setup server environmet
cd pi-remote
npm install

### Run the server
sudo node app.js

### Start server at boot time
Add the following line to /etc/rc.local
tmux new -s remote -d "sudo node /home/pi/GIT/Criben/webinterface-remote-controller/pi-remote/app.js"
