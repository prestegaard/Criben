import paho.mqtt.client as mqtt #import the client1 import time import subprocess
import time
import subprocess
############

flag_connected = 0

def on_connect(client, userdata, flags, rc):
    global flag_connected
    flag_connected = 1
    print("Connected to broker")
    print("Connected with result code "+str(rc))	


def on_message(client, userdata, message):
    print("#### New message ####")
    print("message topic: ", message.topic)   
    print("message payload: " ,str(message.payload.decode("utf-8")))

    if message.topic == "/NAD/":
        cmd = "irsend SEND_ONCE NAD "
        cmd += message.payload.decode("utf-8")
        cmd = cmd.split()   
        print("Calling subprocess: ", cmd)
        subprocess.call(cmd)



########################################
broker_address="192.168.1.17"
print("creating new instance")

#client = mqtt.Client() #create new instance
client = mqtt.Client(client_id="NAD", clean_session=True, userdata=None, protocol=mqtt.MQTTv31, transport="tcp")

client.on_connect = on_connect
client.on_message = on_message #attach function to callback


mqtt_password = ''
with open('password.txt', 'r') as pwfile:
	mqtt_password = pwfile.readline().strip()
#print("Read MQTT Password from file: {}".format(mqtt_password))

client.username_pw_set("haagon", str(mqtt_password))
print("Connecting to broker on ip: ", broker_address)
client.connect(broker_address) #connect to broker
time.sleep(2)

print("Subscribing to topic: /NAD/")
client.subscribe("/NAD/")
time.sleep(2)

print("Loop forever")
client.loop_forever()
