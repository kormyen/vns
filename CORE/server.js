var serialport = require('serialport');
var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var _pduReady = true;
var _lastSent = false;
var _currentKey = '';
var _currentValue = '';

var state = 
{
  lMain:true, 
  lMainB:5,
  lOffice:true, 
  lOfficeB:5,
  lBed:true,
  lBedB:5,
};

// WEB
// app.get('/', function(req, res){
//   res.sendFile(__dirname + '/index.html');
// });
app.use(express.static(__dirname + '/static'));
http.listen(3000, '0.0.0.0', function(){
  console.log('Listening on port 3000');
});

// SERIAL
var receivedData = "";
var port = new serialport('COM6', 
{
  baudRate: 9600,
  // parser: new serialport.parsers.Readline("\n")
  // defaults for Arduino serial communication
  // dataBits: 8, 
  // parity: 'none', 
  // stopBits: 1, 
  // flowControl: false 
});
port.on('error', function(err)
{
  console.log('Error: ', err.message);
})
port.on('open', function()
{
  port.on('data', function(response)
  {
    if (response.toString().trim() == "y")
    {
      _pduReady = true;
      if (_lastSent == false)
      {
        sendCurrentRequest();
      }
    }
    else if (response.toString().trim() == "n")
    {
      console.log('BROKE');
    }
  });
});

// SOCKETIO
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
    _currentKey = data.key;
    _currentInfo = data.info;
    state[data.key] = data.info;
    if (_pduReady)
    {
      sendCurrentRequest();
    }
    else
    {
      _lastSent = false;
    }
  });
});

sendCurrentRequest = function()
{
  _pduReady = false;
  port.write(_currentKey + ' = ' + _currentInfo + ';');
  _lastSent = true;

  var tempState = {};
  tempState[_currentKey] = _currentInfo;
  io.sockets.emit('state', tempState);
}