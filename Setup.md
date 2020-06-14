# Setup
## Pre-requisites
This project has been developed with Arduino. The IDE will be needed to run code on the Arduino. It can be downloaded [here] (https://www.arduino.cc/en/main/software) Note that there may be some issues with opening Arduino IDE on version 1.8.12.  Hence it is recommended you download the Beta Version of Arduino IDE.

## Sensors and Buzzer
The Ultrasonic sensor attached to the ESP8266 board gives us the distance between the sender (our board) and an object based on the time it takes for the sound waves it emits to be reflected back. For this project, if the distance bewteen the ESP8266 board and an objet in front of it is found to be less than 100cm, the buzzer emits a noise.

The DHT11 sensor gives us information about the temperture and humidity. This improves the accuracy of finding the distance between board and object by enbaling us to factor in temperature and humidity in the calculation of the distance apart.

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
