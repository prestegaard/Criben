import paho.mqtt.client as mqtt #import the client1
import time
import subprocess
############

flag_connected = 0

def on_connect(client, userdata, flags, rc):
    global flag_connected
    flag_connected = 1
    print("Connected to broker")


def on_message(client, userdata, message):
    print("#### New message ####")
    print("message received " ,str(message.payload.decode("utf-8")))
    print("message topic=",message.topic)
    #print("message qos=",message.qos)
    #print("message retain flag=",message.retain)
    
    if message.topic == "/NAD/":
        cmd = "irsend SEND_ONCE NAD "
        cmd += message.payload.decode("utf-8")
        cmd = cmd.split()   
        subprocess.call(cmd)

#POWER_OFF
#POWER_ON
#VOLUME+
#VOLUME-
#MUTE
#<a href="/send/NAD/INPUT_CHROMECAST" class="btn btn-primary">Ccast</a>
#<a href="/send/NAD/INPUT_PI" class="btn btn-primary">Wii U</a>
#<a href="/send/NAD/INPUT_SOFA" class="btn btn-primary">Kabel</a>
########################################
broker_address="192.168.1.17"
#broker_address="iot.eclipse.org"
print("creating new instance")
client = mqtt.Client("NAD") #create new instance
#Client(client_id=””, clean_session=True, userdata=None, protocol=MQTTv311, transport=”tcp”)

client.on_connect = on_connect
client.on_message = on_message #attach function to callback
print("connecting to broker")
with open(password.txt, 'r') as pwfile
password = pwfile.readline() 
client.username_pw_set(username='haagon', password=password)
client.connect(broker_address) #connect to broker
#connect(host, port=1883, keepalive=60, bind_address="")
time.sleep(2)

print("Subscribing to topic","/NAD/")
client.subscribe("/NAD/")
time.sleep(2)

print("Loop forever")
client.loop_forever()
#client.loop_start() #start the loop
#print("Publishing message to topic","house/bulbs/bulb1")
#client.publish("house/bulbs/bulb1","OFF")
#time.sleep(10) # wait
#client.loop_stop() #stop the loop
