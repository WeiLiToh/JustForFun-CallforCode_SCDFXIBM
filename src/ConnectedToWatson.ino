#include <ESP8266WiFi.h>
#include "DHT.h"
#include <NewPing.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>

// Watson IoT connection details
#define MQTT_HOST "XXXX.messaging.internetofthings.ibmcloud.com" //Replaced sensitive credentials with "XXXX", originally the orgid.
#define MQTT_PORT 1883
#define MQTT_DEVICEID "d:XXXX:ESP8266:dev01" //Replaced sensitive credentials with "XXXX", originally the orgid.
#define MQTT_USER "use-token-auth"
#define MQTT_TOKEN "XXXX" //Replaced sensitive credentials with "XXXX", originally the orgid.
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
char ssid[] = "XXXX";     //  your network SSID (name). Replaced the sensitive credentials with "XXXX".
char pass[] = "XXXX";  // your network password

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
