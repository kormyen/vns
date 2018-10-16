var serialport = require('serialport');
var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);

const PDUREADY = "y";
const PDUFAIL = "n";

var _pduReady = true;
var _prevPduReqSent = false;
var _currentKey = '';
var _currentInfo = '';

var state = 
{
  lMain:true, 
  lMainB:255,
  lOffice:true, 
  lOfficeB:255,
  lBed:true,
  lBedB:255,
};

// WEB
app.use(express.static(__dirname + '/static'));
http.listen(3000, '0.0.0.0', function(){
  console.log('Listening on port 3000');
});

// WEB STATE SYNC
io.on('connection', function(socket)
{  
  console.log(socket.request.connection.remoteAddress + ' - ' + socket.id + ' - join');
  socket.emit('state', state);

  socket.on('disconnect', function()
  {
    console.log(socket.request.connection.remoteAddress + ' - ' + socket.id + ' - exit');
  });
  socket.on('set', function(data)
  {
    setState(data.key, data.info);
  });
});

// PDU
var pduPort = new serialport('/dev/ttyACM0', { baudRate: 9600 });
pduPort.on('error', function(err)
{
  console.log('Error: ', err.message);
})
pduPort.on('open', function()
{
  pduPort.on('data', function(response)
  {
    if (response.toString().trim() == PDUREADY)
    {
      _pduReady = true;
      if (!_prevPduReqSent)
      {
        sendPduRequest();
      }
    }
    else if (response.toString().trim() == PDUFAIL)
    {
      console.log('BROKE');
    }
  });
});

setState = function(key, value)
{
  console.log('setState: ' + key + ' to: ' + value);
  _currentKey = key;
  _currentInfo = value;
  state[key] = value;
  sendPduRequest();
}

sendPduRequest = function()
{
  if (_pduReady)
  {
    _pduReady = false;
    pduPort.write(_currentKey + ' = ' + _currentInfo + ';');
    _prevPduReqSent = true;

    var tempState = {};
    tempState[_currentKey] = _currentInfo;
    io.sockets.emit('state', tempState);
  }
  else
  {
    _prevPduReqSent = false;
  }  
}

// CONTROL
var controlPort = new serialport('/dev/ttyUSB0', { baudRate: 9600 });
controlPort.on('error', function(err)
{
  console.log('Error: ', err.message);
})
controlPort.on('open', function()
{
  controlPort.on('data', function(response)
  {
    if (response.toString().trim() == '1+')
    {
      setState('lMain', !state.lMain);
    }
  });
});