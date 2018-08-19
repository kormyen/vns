var serialport = require('serialport');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

var _pduReady = true;

// WEB
app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

http.listen(3000, '0.0.0.0', function(){
  console.log('listening on *:3000');
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
    if (_pduReady)
    {
      _pduReady = false;
      port.write('light' + data.key.capitalize() + ' = ' + data.info + ';');
    }
  });
  socket.on('lightBrightness', function(data)
  {
    if (_pduReady)
    {
      _pduReady = false;
      port.write('light' + data.key.capitalize() + ' = ' + data.info + ';');
    }
  });
});

String.prototype.capitalize = function() 
{
  return this.charAt(0).toUpperCase() + this.slice(1);
}