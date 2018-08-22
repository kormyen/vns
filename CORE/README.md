**VNS CORE**

Node.js app running on Raspberry Pi Zero W

Receives input from web UI and/or [CONTROL](https://github.com/kormyen/VNS/tree/master/CONTROL) panel(s), sends commands to [POWER](https://github.com/kormyen/VNS/tree/master/POWER)

<img src='https://raw.githubusercontent.com/kormyen/VNS/master/CORE/000.jpg'>
___

#### Development
```
git clone git@github.com:kormyen/vns.git
cd vns/CORE
npm install
npm start
```
Then visit http://localhost:3000/
___

#### Dependencies

- Runtime: [Node.js](https://nodejs.org/en/)
- Web UI: [Express](https://expressjs.com/)
- State sync: [Socket.io](https://socket.io/)
- Arduino communication: [Serialport](https://node-serialport.github.io/node-serialport/)
___

#### Parts

- [Raspberry Pi Zero W](https://shop.pimoroni.com/products/raspberry-pi-zero-w)
- [4 port USB Hub Hat](https://www.aliexpress.com/item/4-Ports-USB-HUB-HAT-for-Raspberry-Pi-3-2-Zero-W-Extension-Board-USB-to/32826308506.html)
- [Acrylic Case](https://www.aliexpress.com/item/Raspberry-Pi-Zero-W-Case-Acrylic-Case-Black-Aluminum-Heat-Sink-Transparent-Box-compatible-for-Raspberry/32796224314.html)
- [Mini-HDMI to HDMI cable](https://www.aliexpress.com/item/High-speed-Gold-Plated-HDMI-TO-MINI-HDMI-Plug-Male-Male-HDMI-Cable-1M-2M-3M/32840949844.html)
- [16GB C10 Micro SD](https://www.aliexpress.com/item/SanDisk-Extreme-Pro-Ultra-Micro-SD-Memory-Card-SDHC-SDXC-UHS-I-C10-U3-V30-16GB/32834198741.html)
___

#### Raspberry Pi Zero W Setup Guide
**On dev PC**
- Download [Etcher](https://etcher.io/) SD flasher 
- Download [Raspbian Lite](https://www.raspberrypi.org/downloads/raspbian/) OS 
- Write Raspbian Lite to SD card with Etcher

**On Pi**
- Plug in SD card, monitor, keyboard and power
- Login with user `pi` password `raspberry`
- type 'sudo raspi-config'
- setup '1 Change User Password'
- setup '2 Network Options/N1 Hostname'
- setup '2 Network Options/N2 Wi-fi'
- enable '5 Interfacing Options/P2 SSH'
- resize '7 Advanced Options/A1 Expand Filesystem'
- type `reboot`
- type `sudo apt-get update`
- type `sudo apt-get upgrade`
- type `ifconfig`
- record 'inet addr' (your-pi-IP-address)

**On dev PC**
- type `ssh your-pi-IP-address` to connect to pi via ssh

Setup Github SSH:
- type `ssh-keygen -b 2048 -t rsa` to create ssh key
- [add the key to your github account](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/)
- type `ssh -T git@github.com` to test ssh key

Install Git:
- type `sudo apt-get install git`

Install node.js ([reference](https://www.thepolyglotdeveloper.com/2018/03/install-nodejs-raspberry-pi-zero-w-nodesource/)):
- type `curl -o node-v10.9.0-linux-armv6l.tar.gz https://nodejs.org/dist/v10.9.0/node-v10.9.0-linux-armv6l.tar.gz` to download node - [pick correct version from here](https://nodejs.org/dist/)
- type `tar -xzf node-v10.9.0-linux-armv6l.tar.gz` to unzip download
- type `rm -r node-v10.9.0-linux-armv6l.tar.gz` to delete zipped download
- type `sudo cp -R /home/pi/node-v10.9.0-linux-armv6l/* /usr/local/` to install nodejs
- type `sudo rm -r /home/pi/node-v10.9.0-linux-armv6l/` to remove temporary files
- type `nano ~/.profile` to open ".profile" file for editing
- at the end of the file type `PATH=$PATH:/usr/local/bin` to make node and npm commands usable from terminal
- press ctrl+x to to exit nano
- type `yes` to to save
- type `node -v` to test node is installed correctly
- type `npm -v` to test npm is installed correctly

Setup VNS:
- type `git clone git@github.com:kormyen/vns.git` to download repo
- type `cd vns/CORE` to move into node project
- type `npm install` to install node dependencies
- type `npm start` to run VNS
- In a web browser go to `your-pi-IP-address:3000` to access VNS web UI