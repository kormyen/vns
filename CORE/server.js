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

// port.on('open', openPort);
 
// function openPort()
// {
//   console.log('port open');
  
//   port.on('data', function(data)
//   {
//     console.log(data.toString());
//   });
// }

// SOCKETIO
io.on('connection', function(socket)
{
  console.log('a user connected');

  socket.on('disconnect', function()
  {
    console.log('user disconnected');
  });
  socket.on('command', function(msg)
  {
    console.log('command rec: ' + msg);

    if (msg == 'light main true') { port.write('lightMain = true;'); }
    else if (msg == 'light main false') { port.write('lightMain = false;'); }
    else if (msg == 'light office true') { port.write('lightOffice = true;'); }
    else if (msg == 'light office false') { port.write('lightOffice = false;'); }
    else if (msg == 'light bed true') { port.write('lightBed = true;'); }
    else if (msg == 'light bed false') { port.write('lightBed = false;'); }
  });
});