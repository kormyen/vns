**VNS MUSIC**

Airplay receiver running on Raspberry Pi Zero W connected to speakers

#### Setup

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
- type `curl https://get.pimoroni.com/phatdac | bash` ([ref](https://learn.pimoroni.com/tutorial/phat/raspberry-pi-phat-dac-install))
- type `curl -sS get.pimoroni.com/airdac | bash` ([ref](https://learn.pimoroni.com/tutorial/sandyj/streaming-airplay-to-your-pi))

#### Dependencies

- OS: [Raspbian Lite](https://www.raspberrypi.org/downloads/raspbian/)
- Audio player: [Shairport Sync](https://github.com/mikebrady/shairport-sync)

#### Parts

- [Raspberry Pi Zero W](https://shop.pimoroni.com/products/raspberry-pi-zero-w)
- [Pimoroni pHAT DAC](https://shop.pimoroni.com/products/phat-dac) [Alternatives](https://docs.google.com/spreadsheets/d/1iVjY6CdYWONdbuGpj88UIgYQIPR1RHLO_UE1FaU-wOE/)
- [Acrylic Case](https://www.aliexpress.com/item/Raspberry-Pi-Zero-W-Case-Acrylic-Case-Black-Aluminum-Heat-Sink-Transparent-Box-compatible-for-Raspberry/32796224314.html)
- 8GB C10 Micro SD