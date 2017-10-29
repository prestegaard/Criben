

var changeTab = function(event) {
  event.preventDefault()
  var link = this;
  var $link = $(link);
  var name = $link.text().trim();
  var remote = name.toLowerCase();



  $("#tabBar li").removeClass("active");
  $link.parents("li").addClass("active");
  $(".remote-screen").addClass("hidden");
  $("#"+remote).removeClass("hidden");
  document.title = "Remote - "+name;
  window.scroll(0);
};

$("#tabBar a").bind("click touchstart",changeTab)


$(".remote-screen a").click(function(event) {
var $this = $(this);
  document.body.style.opacity = "0.5";

$.ajax({
  url: $(this).attr("href"),
}).done(function(data) {
	console.log(data);
	console.log($this);
  document.body.style.opacity="1"
});
event.preventDefault()
return true;
});
/**
 * Converts :hover CSS to :active CSS on mobile devices.
 * Otherwise, when tapping a button on a mobile device, the button stays in
 * the :hover state until the button is pressed. 
 *
 * Inspired by: https://gist.github.com/rcmachado/7303143
 * @author  Michael Vartan <michael@mvartan.com>
 * @version 1.0 
 * @date    2014-12-20
 */
function hoverTouchUnstick() {
  // Check if the device supports touch events
  if('ontouchstart' in document.documentElement) {
    // Loop through each stylesheet
    for(var sheetIndex = document.styleSheets.length - 1; sheetIndex >= 0; sheetIndex--) {
      var sheet = document.styleSheets[sheetIndex];
      // Verify if cssRules exists in sheet
      if(sheet.cssRules) {
        // Loop through each rule in sheet
        for(var ruleIndex = sheet.cssRules.length - 1; ruleIndex >= 0; ruleIndex--) {
          var rule = sheet.cssRules[ruleIndex];
          // Verify rule has selector text
          if(rule.selectorText) {
            // Replace hover psuedo-class with active psuedo-class
            rule.selectorText = rule.selectorText.replace(":hover", ":active");
          }
        }
      }
    }
  }
}
  hoverTouchUnstick();
var sendKey = function(remote_name, key_name) {
    document.body.style.opacity = "0.5";

$.ajax({
  url: "/send/"+remote_name+"/"+key_name
}).done(function(data) {
  console.log(data);
  document.body.style.opacity="1"
});  
};

$("#type").bind('change input',function(event) {
  var $this = $(this);
  var text = this.value;
  var deviceName = "vizio";
  //console.log("\""+text+"\"")
  $this.val("");
  var placeHolderText = $this.attr("placeholder");
  if(placeHolderText === "Type here") placeHolderText = "";
  if(text === "") text = " ";
  $this.removeClass("text-center").addClass("text-right")
  if(placeHolderText.length>30)
    placeHolderText = placeHolderText.substring(1);
  $this.attr("placeholder",placeHolderText+text)
  if(text.length>0) {
    switch(text) {
      case " ":
        text = "SPACE";
        deviceName = "vizio_2";
        break;
      case ".":
        text = "DOT";
        break;
      case "/":
        text = "SLASH";
        break;
    }
    sendKey(deviceName, text.toUpperCase())
  }

  //console.log(text)
});

$("#type").bind('keyup', function(event) {
  var keyName = "";
  $type = $("#type");
  placeHolderText = $type.attr("placeholder");
  switch(event.which) {
    case 8:
      keyName = "BACKSPACE";
      if(placeHolderText.length>0)
        $type.attr("placeholder", placeHolderText.substr(0,placeHolderText.length-1));
      break;
    case 13:
      keyName = "ENTER";
      $type.attr("placeholder", "");
      break;

    default: return;
  }
  sendKey("NAD", keyName);
});




$(document).ready(function() {

    var socket = io.connect('http://localhost:80');

    socket.on('connect', function (data) {
        socket.emit('join', 'Hello World from client');
    });


    socket.on('init', function (data) {
        $('#header_test').append("<br/>" + data.color_hue);
        $('#header_test').append("<br/>" + data.color_sat);
        $('#header_test').append("<br/>" + data.color_val);
        $('#color_hue_value').html(data.color_hue);
        $("#color_hue_slider").val(data.color_hue);
        $("#color_hue_slider").trigger('change');

        $('#color_sat_value').html(data.color_sat);
        $("#color_sat_slider").val(data.color_sat);
        $("#color_sat_slider").trigger('change');

        $('#color_val_value').html(data.color_val);
        $("#color_val_slider").val(data.color_val);
        $("#color_val_slider").trigger('change');


    });

    socket.on('broad', function (data) {
        $('#future').append(data + "<br/>");
    });

    $('form').submit(function (e) {
        e.preventDefault();
        var message = $('#chat_input').val();
        socket.emit('messages', message);
    });

    document.getElementById("color_settings_button").addEventListener("click", myFunction);

    function updateColorsFunction() {
        document.getElementById("demo").innerHTML = "YOU CLICKED ME!";
        var color_hue = document.getElementById("color_hue_value");
        var color_sat = document.getElementById("color_sat_value");
        var color_val = document.getElementById("color_val_value");
        socket.emit('updateColors', {color_hue: color_hue, color_sat: color_sat, color_val: color_val});

    }
};