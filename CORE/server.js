var serialport = require('serialport');
var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);

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
  // parser: new SerialPort.parsers.Readline('\n'),
  // defaults for Arduino serial communication
  dataBits: 8, 
  parity: 'none', 
  stopBits: 1, 
  flowControl: false 
});

port.on('error', function(err)
{
  console.log('Error: ', err.message);
})

// SOCKETIO
io.on('connection', function(socket)
{
  console.log('a user connected');

  socket.on('disconnect', function()
  {
    console.log('user disconnected');
  });
  socket.on('lightToggle', function(data)
  {
    console.log('Toggle ' + data.key + ' light to ' + data.info);
    port.write('light' + data.key.capitalize() + ' = ' + data.info + ';');
  });
  socket.on('lightBrightness', function(data)
  {
    console.log('Set brightness of ' + data.key + ' light to ' + data.info);
    port.write('light' + data.key.capitalize() + ' = ' + data.info + ';');
  });
});

String.prototype.capitalize = function() 
{
  return this.charAt(0).toUpperCase() + this.slice(1);
}