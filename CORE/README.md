**VNS CORE**

Node.js app running on Raspberry Pi Zero W

Receives input from web UI and/or [CONTROL](https://github.com/kormyen/VNS/tree/master/CONTROL) panel(s), sends commands to [POWER](https://github.com/kormyen/VNS/tree/master/POWER)

#### Development
```
git clone git@github.com:kormyen/vns.git
cd vns
cd CORE
npm install
npm start
```
Then visit http://localhost:3000/

#### Dependencies

- Runtime: [Node.js](https://nodejs.org/en/)
- Web UI: [Express](https://expressjs.com/)
- State sync: [Socket.io](https://socket.io/)
- Arduino communication: [Serialport](https://node-serialport.github.io/node-serialport/)