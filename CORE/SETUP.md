#### Raspberry Pi Zero W Setup Guide

**On dev PC**
- Download [Etcher](https://etcher.io/) SD flasher 
- Download [Raspbian Lite](https://www.raspberrypi.org/downloads/raspbian/) OS 
- Write Raspbian Lite to SD card with Etcher

**On Pi**
- Plug in SD card, monitor, keyboard and power
- Login with user `pi` password `raspberry`
- type 'sudo raspi-config'
- setup '2 Network Options/N1 Hostname' (Computer's name)
- setup '1 Change User Password'
- setup '2 Network Options/N2 Wi-fi'
- enable '5 Interfacing Options/P2 SSH'
- resize '7 Advanced Options/A1 Expand Filesystem'
- accept rebooting after closing raspi-config
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

Setup VNS service ([reference](https://www.paulaikman.co.uk/nodejs-services-raspberrypi/))
- type `sudo nano /lib/systemd/system/vnscore.service`
- paste the content of [vnscore.service](vnscore.service):
```
[Unit]
Description=VNS Core Nodejs server
After=multi-user.target

[Service]
Type=idle
ExecStart=/bin/bash -c 'exec /usr/local/bin/node /home/pi/vns/CORE/server.js >> /home/pi/vnscore.log 2>&1' # log console output to log

[Install]
WantedBy=multi-user.target
```
- press ctrl+x to to exit nano
- type `yes` to to save
- type `sudo chmod 644 /lib/systemd/system/vnscore.service` to allow it to be run
- type `sudo systemctl daemon-reload` to reload service list
- type `sudo systemctl enable vnscore.service` to enable vnscore service
- type `sudo systemctl start vnscore.service` to start vnscore service
- type `sudo systemctl status vnscore.service` to check vnscore service is running

VNS CORE should now automatically run when the pi boots.
