# VNS CORE

Node.js app running on Raspberry Pi Zero W

Receives input from web UI and Arduino control panel(s), sends commands to [__Power__ Distribution](https://github.com/kormyen/VNS/tree/master/POWER)

#### Development
```
cd CORE
npm install
npm start
```
Visit http://localhost:3000/

#### Dependencies

- Runtime: [Node.js](https://nodejs.org/en/)
- Web UI: [Express](https://expressjs.com/)
- Arduino communication: [Serialport](https://node-serialport.github.io/node-serialport/)