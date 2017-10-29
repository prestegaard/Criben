/**
 * app.js
 * 
 * IR Remote Web Service
 * 
 * @author Michael Vartan
 * @version 1.0.0 
 */



var express = require('express');
var app = express();
var exec = require('child_process').exec;
var server = require('http').createServer(app);
var io = require('socket.io')(server);


// LED Parameters
var color_hue = 0;
var color_sat = 255;
var color_val = 128;

/**
 * Dictionary of devices and their buttons
 * @type {Object}
 */
var devices = {};
/**
 * Generates function to get devices' buttons from irsend command
 * @param  {String} deviceName name of device
 * @return {Function}            exec callback
 */ 
var getCommandsForDevice = function(deviceName) {
  /**
   * Get Device's Button from irsend command
   * @param  {String} error  Error from running command
   * @param  {String} stdout std out
   * @param  {String} stderr std err
   * @return {None}        
   */
  return function(error, stdout, stderr) {
    var lines = stderr.split("\n");
    for(var lineIndex in lines) {
      var line = lines[lineIndex];
      var parts = line.split(" ");
      if(parts.length>2) {
        var keyName = parts[2];
        devices[deviceName].push(keyName);
        console.log(deviceName + " found key: "+keyName);
      }
    }
  }
};
/**
 * Get Device from irsend command
 * @param  {String} error  Error from running command
 * @param  {String} stdout std out
 * @param  {String} stderr std err
 * @return {None}        
 */
var getDevice = function (error, stdout, stderr) {
  if(error) {
    console.log("irsend not available.");
    return;
  }
  var lines = stderr.split("\n");
  for(var lineIndex in lines) {
    var line = lines[lineIndex];
    var parts = line.split(" ");
    if(parts.length>1) {
      var deviceName = parts[1];
      console.log("device found: "+deviceName.trim());
      devices[deviceName] = [];
      exec("irsend list \""+deviceName+"\" \"\"", getCommandsForDevice(deviceName));

    }
  }          
};
// Get all device information
exec("irsend list \"\" \"\"", getDevice);

// Define static HTML files
app.use(express.static(__dirname + '/html'));

app.get('/nrk1', function(req, res) {
	exec("omxplayer -b -r -o hdmi udp://@239.1.2.11:1234", function(error, stdout, sterr){
   	 	if(error)
    	  		res.send("Error sending command nrk1");
  });
  

});
app.get('/tv2', function(req, res) {
	exec("omxplayer -r -b -o hdmi udp://@233.155.107.1:57000", function(error, stdout, sterr){
   	 	if(error)
    	  		res.send("Error sending command tv2");
  });
  

});
app.get('/zebra', function(req, res) {
	exec("omxplayer -b -r -o hmdi udp://@233.155.107.102:5700", function(error, stdout, sterr){
   	 	if(error)
    	  		res.send("Error sending command zebra");
  });
});


app.get('/music', function(req, res) {
  res.redirect('/index.html');
});

app.get('/lights', function(req, res) {
  res.redirect('/lights.html');
});



// define GET request for /led/cmd
app.get('/led/:cmd', function(req, res) {
    var cmd = req.param("cmd");
    console.log("LED CMD: " + cmd);
    //res.send("CMD: "+cmd);
    res.redirect('/lights.html');

});


// define GET request for /send/deviceName/buttonName
app.get('/send/:device/:key', function(req, res) {

  var deviceName = req.param("device");
  var key = req.param("key").toUpperCase();
  console.log("MUSIC CMD: " + key);
  // Make sure that the user has requested a valid device 
  if(!devices.hasOwnProperty(deviceName)) {
    res.send("invalid device");
    return;
  }

  // Make sure that the user has requested a valid key/button
  var device = devices[deviceName];
  var deviceKeyFound = false;
  for(var i = 0; i < device.length; i++) {
    if(device[i] === key) {
      deviceKeyFound = true; 
      break;
    }
  }
  if(!deviceKeyFound) {
    res.send("invalid key number: "+key);
    return;
  }

  // send command to irsend
  var command = "irsend SEND_ONCE "+deviceName+" "+key;
  exec(command, function(error, stdout, stderr){
    if(error)
      res.send("Error sending command");
    else
	res.redirect('/index.html');
	//res.sendFile(__dirname + '/html'+'/index.html');   
	//res.send("Successfully sent command");
  });


}); // end define GET request for /send/deviceName/buttonName


/* Connection events */
io.on('connection', function(client) {
    console.log('Client connected...');
    //socket.emit("send planes", {x:x, y:y, z:z, name: name});
    client.emit('init', {color_hue:color_hue, color_sat:color_sat, color_val:color_val});


    client.on('join', function(data) {
        console.log(data);
        data = "halla fra server";
        client.emit('connect', data);
    });

    client.on('messages', function(data) {
        console.log(data)
        data += " from server";
        client.emit('broad', data);
        client.broadcast.emit('broad',data);
    });

    client.on('updateColors', function(data) {
        console.log("UPDATE COLORS: " + data.color_hue);
        color_hue = data.color_hue;
        color_sat = data.color_sat;
        color_val = data.color_val;
    });

});



// Listen on port 80
server.listen(80);


