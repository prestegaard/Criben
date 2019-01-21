# NAD-ir-remote
Control for NAD T474 with web interface.
Project is based upon this https://github.com/vartan/pi-remote.git
Rasbian version working is http://downloads.raspberrypi.org/raspbian_lite/images/raspbian_lite-2016-02-29/


### Packages
```
sudo apt-get install lirc
curl -L https://npmjs.org/install.sh | sudo sh
#install latest node deb package included with 
sudo dpkg -i
```
### Files
Add the following line to /boot/config.txt
```
dtoverlay=lirc-rpi,gpio_out_pin=16,gpio_in_pin=18
```
Add the following to /etc/wpa_supplicant/wpa_supplicant.conf
```

ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
network={
        ssid="SSID"
        psk="mypassword"
}
```
Remember to include quotes



Swap /etc/lirc/ with the included files

### Setup server environmet
```
cd pi-remote
npm install
```
### Run the server
```
sudo node app.js
```
### Start server at boot time
Add the following line to /etc/rc.local
```
tmux new -s remote -d "sudo node /home/pi/GIT/Criben/webinterface-remote-controller/pi-remote/app.js"
```

# Home Automation
Home automation control for ac outlets, lights, temperature, etc. 
Webpage control is based upon this https://github.com/vartan/pi-remote.git

## Setup

### Packages
```bash
sudo apt-get install tmux
```

### Node
1) Get Node
	+ Download lates NODE ARM6 for Raspberry Pi 1B or ARM7 for Pi 2 and 3 from [NodeJS](https://nodejs.org/en/download/) 
	+ Or use included tarball downloaded 07.06.2017 for Pi1
2) Install Node
```bash
# Unzip: 
tar -xvf node-v*
# Enter folder: 
cd node-v*
# Install:
sudo cp -R * /usr/local/
```

### Files
No files change yet

### Setup server environment
```bash
cd webserver
npm install
```

## Run the webserver
```bash
sudo node webserver/app.js
```


