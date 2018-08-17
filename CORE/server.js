var serialport = require('serialport');
var express = require('express');
var app = express();

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
 
function openPort()
{
  console.log('port open');
  
  port.on('data', function(data)
  {
    console.log(data.toString());
  });
}

// WEB
app.use(express.static(__dirname + '/public')); // exposes index.html, per below

app.get('/mainon', function(req, res)
{
  port.write('lightMain = true;');
  console.log('MAIN ON');
});
app.get('/mainoff', function(req, res)
{
  port.write('lightMain = false;');
  console.log('MAIN OFF');
});
app.get('/officeon', function(req, res)
{
  port.write('lightOffice = true;');
  console.log('OFFICE ON');
});
app.get('/officeoff', function(req, res)
{
  port.write('lightOffice = false;');
  console.log('OFFICE OFF');
});
app.get('/bedon', function(req, res)
{
  port.write('lightBed = true;');
  console.log('BED ON');
});
app.get('/bedoff', function(req, res)
{
  port.write('lightBed = false;');
  console.log('BED OFF');
});

app.listen(3000, () => console.log('Server listening on port 3000'));