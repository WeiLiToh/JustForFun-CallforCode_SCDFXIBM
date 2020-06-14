## Sensors and Buzzer
The Ultrasonic sensor attached to the ESP8266 board gives us the distance between the sender (our board) and an object based on the time it takes for the sound waves it emits to be reflected back. For this project, if the distance between the ESP8266 board and an object in front of it is found to be less than 100cm, the buzzer emits a noise.

The DHT11 sensor gives us information about the temperture and humidity. This improves the accuracy of finding the distance between board and object by enbaling us to factor in temperature and humidity in the calculation of the distance apart.

## Circuit Diagram
(Note: Have some problems generating schematic on Fritzing. However, this would be a circuit diagram of how the components are being wired together in this project)

![wiringDiagram](https://user-images.githubusercontent.com/62842333/84584757-ca160b80-ae3a-11ea-84e1-079f564a9441.PNG)

# Arduino Code Sketch 
``` c++ 
// Watson IoT connection details, Sensitive Credentials have been replaced with "XXXX"
#define MQTT_HOST "XXXXXX.messaging.internetofthings.ibmcloud.com" 
#define MQTT_PORT 1883
#define MQTT_DEVICEID "d:XXXXXX:YYYY:ZZZZ" 
#define MQTT_USER "use-token-auth"
#define MQTT_TOKEN "PPPP" 
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
#define MQTT_TOPIC_DISPLAY "iot-2/cmd/display/fmt/json"
```
Above shows a crucial part of our code that enbales us to get our device connected to Watson IoT. 
Some of these values have to be changed to match your configuration:
- XXXXXX should be the 6 character Organisation ID for your platform. The organisation ID can be obtained under the settings section of the IoT Platform console. Under identity, you will see the value to use.
- YYYY is the device type you used for the ESP8266 device. This should be ESP8266. 
- PPPP is the token you used when registering the device 
- ZZZZ is the device ID for your ESP8266, you can use dev01 for this.

# Node-RED
Let's analyze our Node-RED flow and understand how it's flow works.

![image](https://user-images.githubusercontent.com/62842333/84583932-6dfab980-ae31-11ea-8600-345b71b0d44e.png)

- MQTT in: Connects our device to Node-RED. The data we are sending is parsed as a JSON object into this node. This node enables us to obtain the distance between our user and other members of the public.

- change: Our msg.payload from our MQTT in node is a JSON object that not only contains our distance value, but also our temperature, humidity and echo time values. The change node sets the msg.payload such that we only obtain the value we are interested in, the distance (It sets msg.pauload to msg.payload.d.distance). 

- function: When social distancing measure has been violated, function will be True and an SMS will be sent to the user who has violated it. The msg.payload consists of an if statement to check if the value of msg.payload is less than 100.
- debug: debug node is set to output the msg.payload, helps to verify if the change node is successful in extracting only the distance value.

- send SMS: When function node is true, this node will be triggered and an SMS will be sent to the user who has violated the social distancing measure


