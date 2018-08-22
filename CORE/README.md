**VNS CORE**

Node.js app running on Raspberry Pi Zero W

Receives input from web UI and/or [CONTROL](https://github.com/kormyen/VNS/tree/master/CONTROL) panel(s), sends commands to [POWER](https://github.com/kormyen/VNS/tree/master/POWER)

<img src='https://raw.githubusercontent.com/kormyen/VNS/master/CORE/000.jpg'>

#### Development
```
git clone git@github.com:kormyen/vns.git
cd vns/CORE
npm install
npm start
```
Then visit http://localhost:3000/

#### Dependencies

- Runtime: [Node.js](https://nodejs.org/en/)
- Web UI: [Express](https://expressjs.com/)
- State sync: [Socket.io](https://socket.io/)
- Arduino communication: [Serialport](https://node-serialport.github.io/node-serialport/)

#### Parts

- [Raspberry Pi Zero W](https://shop.pimoroni.com/products/raspberry-pi-zero-w)
- [4 port USB Hub Hat](https://www.aliexpress.com/item/4-Ports-USB-HUB-HAT-for-Raspberry-Pi-3-2-Zero-W-Extension-Board-USB-to/32826308506.html)
- [Acrylic Case](https://www.aliexpress.com/item/Raspberry-Pi-Zero-W-Case-Acrylic-Case-Black-Aluminum-Heat-Sink-Transparent-Box-compatible-for-Raspberry/32796224314.html)
- [Mini-HDMI to HDMI cable](https://www.aliexpress.com/item/High-speed-Gold-Plated-HDMI-TO-MINI-HDMI-Plug-Male-Male-HDMI-Cable-1M-2M-3M/32840949844.html)
- [16GB C10 Micro SD](https://www.aliexpress.com/item/SanDisk-Extreme-Pro-Ultra-Micro-SD-Memory-Card-SDHC-SDXC-UHS-I-C10-U3-V30-16GB/32834198741.html)