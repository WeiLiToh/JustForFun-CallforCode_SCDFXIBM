#include "DHT.h"
#include <NewPing.h>

#define DHTPIN 4
#define DHTTYPE DHT11 //using DHT11 sensor
#define TRIGGER D7
#define ECHO    D6
#define BUZZER_PIN D3

int maxDist = 400; //set maximum scan distance to 100cm
int echoTime; //echo time
float distance; //distance(cm)

NewPing sonar(TRIGGER, ECHO,maxDist);
DHT dht(DHTPIN, DHTTYPE);

// NodeMCU Pin D1 > TRIGGER | Pin D2 > ECHO
 
void setup() {
  Serial.begin (115200);
  
  dht.begin();//intialising sensor library 
  
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(BUILTIN_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}
 
void loop() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(2000);
  
  echoTime = sonar.ping(); //echo time (μs)

  float humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float temperature = dht.readTemperature();
    
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float vsound = 331.3 + (0.606*temperature)+(0.0124*humidity);
  distance = (echoTime/2.0)*vsound/10000; //distance between sensor and target
 
  Serial.print("\techo time: ");    
  Serial.print(echoTime);         
  Serial.print(" microsecs\t"); 
  Serial.print("distance: ");    
  Serial.print(distance,2);      
  Serial.print(" cm");  


  if (distance<100 && distance >= 0){
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else if (distance > 100){
    digitalWrite(BUZZER_PIN, LOW);
  }
  
  delay(1000);
}
