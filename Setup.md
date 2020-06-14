# Setup
## Pre-requisites
This project has been developed with Arduino. The IDE will be needed to run code on the Arduino. It can be downloaded [here] (https://www.arduino.cc/en/main/software) Note that there may be some issues with opening Arduino IDE on version 1.8.12.  Hence it is recommended you download the Beta Version of Arduino IDE.

## Sensors and Buzzer
The Ultrasonic sensor attached to the ESP8266 board gives us the distance between the sender (our board) and an object based on the time it takes for the sound waves it emits to be reflected back. For this project, if the distance bewteen the ESP8266 board and an objet in front of it is found to be less than 100cm, the buzzer emits a noise.

The DHT11 sensor gives us information about the temperture and humidity. This improves the accuracy of finding the distance between board and object by enbaling us to factor in temperature and humidity in the calculation of the distance apart.

## Circuit Diagram
(Note: Have some problems generating schematic on Fritzing. However, this would be a circuit diagram of how the components are being wired together in this project)

![wiringDiagram](https://user-images.githubusercontent.com/62842333/84584757-ca160b80-ae3a-11ea-84e1-079f564a9441.PNG)

## Driver Installation
### Windows/Linux
The next step would be to install the required drivers for our ESP8266 module. Windows and Linux installations can be downloaded [here] (https://github.com/nodemcu/nodemcu-devkit/tree/master/Drivers) Select the appropriate one for your OS, download it, unzip it and install it.

### MacOS 
The manufacturer's web site (http://www.wch.cn/download/CH341SER_MAC_ZIP.html) , in Chinese, for the USB driver chip on the LoLin NodeNCU board - translate with Google Chrome, then click on download ink to access the macOS driver. After installing goto System Preferences -> Security and Privacy to allow the driver to be loaded.

### Installing ESP8266 Plugin for the Arduino IDE
A plugin is needed to the Arduino IDE in order for it to suppport ESP8266 development. Launch the Arduino IDE then open up preferences panle for Arduino IDE:
- Linux : File -> Preferences
- MacOS : Arduino -> Preferences
- Windows : File -> Preferences

Paste in the URL for the ESP plugin to the Additional Board Managers URLs field:
http://arduino.esp8266.com/stable/package_esp8266com_index.json

Select OK to close the preferences dialog.

Select *Tools -> Board: -> Board Manager...* from the menu, then enter ESP in the search box. Install the plugin **esp8266 by ESP8266 community**. Click inside the esp8266 box then press install to install the latest plugin. Once installed close the board manager. 

### Installing libraries for the project
After launching the Arduino IDE, go to the sketch menu, select "Include library" and finally "Manage Libraries", then search and install the following libraries

- ArduinoJson by Benoit Blanchon Version 6.15.2
- NewPing by Tim Eckel Version 1.9.1. This library improves the performance of our ultrasonic sensor.
- DHT sensor library by Adafruit Version 1.3.10
- PubSubClient by Nick O'Leary Version 2.8.0. This library will allow us to send and receive MQTT messages.

### Installing filesystemupload tool for ESP8266 
The ESP8266 has flash memory that can hold a filesystem. There is a plugin for Arduino that allows you to generate a populated filesystem and upload it to the ESP8266 board. The plugin can be downloaded from here [here](https://github.com/esp8266/arduino-esp8266fs-plugin/releases) . You need to create a tools directory within the sketch directory then extract the content there.

![image](https://user-images.githubusercontent.com/62842333/84583354-4e13c780-ae2a-11ea-902b-00bb15eed80f.png)

Your sketch directory's location can be found from the preferences panel of the Arduino IDE). Default location of sketch directory is:

- Linux - **/home/< user name >/Arduino/tools/ESP8266FS**
- MacOS - **/Users/< user name >/Documents/Arduino/tools/ESP8266FS**
- Windows - **C:\Users< user name >\Documents\Arduino\tools\ESP8266FS**

# IBM Cloud account Signup
This project uses services hosted on the IBM Cloud, so take some time to [signup](https://cloud.ibm.com/login) for a free account. 

# Setting up our Internet of Things platform
Before registering our device on the IoT platform, we would have to deploy a starter application to the IBM Cloud. This project uses the same method found [here](https://github.com/binnes/esp8266Workshop/blob/master/en/part1/IOTCLOUD.md) to deploy our starter application.

After deploying our application, registration of the device would be very straightforward. Simply click on register new devices and thanks to the code we have uploaded to our microcontroller, we're able to perform remote actions on our device with ease. 

Our Node-RED app has to be created next, in order for us to send messages to those who have breached safety distancing measures and seek to correct them using our SMS messages. 

# Node-RED
Let's analyze our Node-RED flow and understand how it's flow works.

![image](https://user-images.githubusercontent.com/62842333/84583932-6dfab980-ae31-11ea-8600-345b71b0d44e.png)

- MQTT in: Connects our device to Node-RED. The data we are sending is parsed as a JSON object into this node. This node enables us to obtain the distance between our user and other members of the public.

- change: Our msg.payload from our MQTT in node is a JSON object that not only contains our distance value, but also our temperature, humidity and echo time values. The change node sets the msg.payload such that we only obtain the value we are interested in, the distance (It sets msg.pauload to msg.payload.d.distance). 

- function: When social distancing measure has been violated, function will be True and an SMS will be sent to the user who has violated it. The msg.payload consists of an if statement to check if the value of msg.payload is less than 100.
- debug: debug node is set to output the msg.payload, helps to verify if the change node is successful in extracting only the distance value.

- send SMS: When function node is true, this node will be triggered and an SMS will be sent to the user who has violated the social distancing measure


