var serialport = require('serialport');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var _pduReady = true;
var _lastSent = false;
var _currentRequest = '';

// WEB
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});
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
  console.log('connection');

  socket.on('disconnect', function()
  {
    console.log('disconnection');
  });
  socket.on('lightToggle', function(data)
  {
    _currentRequest = 'light' + data.key.capitalize() + ' = ' + data.info + ';';
    if (_pduReady)
    {
      sendCurrentRequest();
    }
    else
    {
      _lastSent = false;
    }
  });
  socket.on('lightBrightness', function(data)
  {
    _currentRequest = 'light' + data.key.capitalize() + ' = ' + data.info + ';';
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
  port.write(_currentRequest);
  _lastSent = true;
}

String.prototype.capitalize = function() 
{
  return this.charAt(0).toUpperCase() + this.slice(1);
}