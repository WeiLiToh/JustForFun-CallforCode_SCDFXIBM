## Sensors and Buzzer
The Ultrasonic sensor attached to the ESP8266 board gives us the distance between the sender (our board) and an object based on the time it takes for the sound waves it emits to be reflected back. For this project, if the distance bewteen the ESP8266 board and an objet in front of it is found to be less than 100cm, the buzzer emits a noise.

The DHT11 sensor gives us information about the temperture and humidity. This improves the accuracy of finding the distance between board and object by enbaling us to factor in temperature and humidity in the calculation of the distance apart.

## Circuit Diagram
(Note: Have some problems generating schematic on Fritzing. However, this would be a circuit diagram of how the components are being wired together in this project)

![wiringDiagram](https://user-images.githubusercontent.com/62842333/84584757-ca160b80-ae3a-11ea-84e1-079f564a9441.PNG)

# Arduino Code Sketch 
``` c++ 
#include <ESP8266WiFi.h>
#include "DHT.h"
#include <NewPing.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Watson IoT connection details
#define MQTT_HOST "0f78uu.messaging.internetofthings.ibmcloud.com"
#define MQTT_PORT 1883
#define MQTT_DEVICEID "d:0f78uu:ESP8266:dev01"
#define MQTT_USER "use-token-auth"
#define MQTT_TOKEN "W@sd15417"
#define MQTT_TOPIC "iot-2/evt/status/fmt/json"
#define MQTT_TOPIC_DISPLAY "iot-2/cmd/display/fmt/json"

// Add GPIO pins used to connect devices
#define DHTPIN 4 // GPIO pin the data line of the DHT sensor is connected to
#define DHTTYPE DHT11 //using DHT11 sensor
#define TRIGGER D7
#define ECHO    D6
#define BUZZER_PIN D3

int maxDist = 400; //set maximum scan distance to 100cm
int echoTime; //echo time
float distance; //distance(cm)

// Add WiFi connection information
char ssid[] = "SINGTEL-BC30(2.4G)";     //  your network SSID (name)
char pass[] = "eexaisohph";  // your network password

NewPing sonar(TRIGGER, ECHO,maxDist);
DHT dht(DHTPIN, DHTTYPE);

// MQTT objects
void callback(char* topic, byte* payload, unsigned int length);
WiFiClient wifiClient;
PubSubClient mqtt(MQTT_HOST, MQTT_PORT, callback, wifiClient);

// variables to hold data
StaticJsonDocument<100> jsonDoc;
JsonObject payload = jsonDoc.to<JsonObject>();
JsonObject status = payload.createNestedObject("d");
static char msg[50];

float humidity = 0.0;
float temperature = 0.0;

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] : ");
  
  payload[length] = 0; // ensure valid content is zero terminated so can treat as c-string
  Serial.println((char *)payload);
}
 
void setup() {
  Serial.begin (115200);
  Serial.setTimeout(2000);
  while (!Serial) { }
  Serial.println();
  Serial.println("ESP8266 Sensor Application");

  // Start WiFi connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");

  // Start connected devices
  dht.begin();//intialising sensor library 
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to MQTT - IBM Watson IoT Platform
  if (mqtt.connect(MQTT_DEVICEID, MQTT_USER, MQTT_TOKEN)) {
    Serial.println("MQTT Connected");
    mqtt.subscribe(MQTT_TOPIC_DISPLAY);

  } else {
    Serial.println("MQTT Failed to connect!");
    ESP.reset();
  }
}
 
void loop() {
  mqtt.loop();
  while (!mqtt.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqtt.connect(MQTT_DEVICEID, MQTT_USER, MQTT_TOKEN)) {
      Serial.println("MQTT Connected");
      mqtt.subscribe(MQTT_TOPIC_DISPLAY);
      mqtt.loop();
    } else {
      Serial.println("MQTT Failed to connect!");
      delay(5000);
    }
  }
  
  echoTime = sonar.ping(); //echo time (μs)

  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();

  float vsound = 331.3 + (0.606*temperature)+(0.0124*humidity);
  distance = (echoTime/2.0)*vsound/10000; //distance between sensor and target

  if (distance<100 && distance >= 0){
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else if (distance > 100){
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
  } else {
    // Send data to Watson IoT Platform
    status["temp"] = temperature;
    status["humidity"] = humidity;
    status["echoTime"] = echoTime;
    status["distance"] = distance;
    serializeJson(jsonDoc, msg, 100);
    Serial.println(msg);
    if (!mqtt.publish(MQTT_TOPIC, msg)) {
      Serial.println("MQTT Publish failed");
    }
  }

  // Pause - but keep polling MQTT for incoming messages
  for (int i = 0; i < 10; i++) {
    mqtt.loop();
    delay(1000);
  }
 
  delay(1000);
}
```

# Node-RED
Let's analyze our Node-RED flow and understand how it's flow works.

![image](https://user-images.githubusercontent.com/62842333/84583932-6dfab980-ae31-11ea-8600-345b71b0d44e.png)

- MQTT in: Connects our device to Node-RED. The data we are sending is parsed as a JSON object into this node. This node enables us to obtain the distance between our user and other members of the public.

- change: Our msg.payload from our MQTT in node is a JSON object that not only contains our distance value, but also our temperature, humidity and echo time values. The change node sets the msg.payload such that we only obtain the value we are interested in, the distance (It sets msg.pauload to msg.payload.d.distance). 

- function: When social distancing measure has been violated, function will be True and an SMS will be sent to the user who has violated it. The msg.payload consists of an if statement to check if the value of msg.payload is less than 100.
- debug: debug node is set to output the msg.payload, helps to verify if the change node is successful in extracting only the distance value.

- send SMS: When function node is true, this node will be triggered and an SMS will be sent to the user who has violated the social distancing measure


