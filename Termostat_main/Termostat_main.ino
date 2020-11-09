/*
  ------------------------------
    Thermostat Control System
    Verision: 1.0
  ------------------------------
*/

// Includes Temperature
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Inculdes Servo
#include <Servo.h>

// MG995 Setup
Servo servoT;
#define MGPIN 9

// DHT22 Setup
#define DHTPIN 12
#define DHT5V 13
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// ---- Global variables ----
float currTemp = 20.0;
float calibration = 23.10 - 22.7; // DHT - Fluke  // 2020-11-09
float refTemp = 22.0;

// ---------- Setup ----------
void setup() 
{
  // Begin Serial
  Serial.begin(9600);
  
  // Pullup resistor for data signal
  pinMode(DHTPIN, INPUT_PULLUP);

  // 5V Pin to Sensor
  pinMode(DHT5V, OUTPUT);

  // Begin Sensor
  dht.begin();
  Serial.println(F("Sensor is now online"));

  // Add and move to off
  servoT.attach(MGPIN);
  servoT.write(180);
  Serial.println(F("Servo is now at position 180 (Off)")); 
  
  // Done
  Serial.println(F("Termostat is now running:"));
}

// ---------- Loop ----------
void loop() 
{
  // Get temperature
  digitalWrite(DHT5V, HIGH);
  delay(1000);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  digitalWrite(DHT5V, LOW);

  // Save and print temperature
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature"));
  }
  else {
    // Update reading using calibration
    currTemp = event.temperature - calibration;

    // Print temperature
    Serial.println(currTemp);
  }

  // Temperature logic for servo control
  if (currTemp >= refTemp)
  {
    servoT.write(180);
    Serial.println(F("Servo is now ar position 180 (Off)"));
    
  }else if (currTemp <= (refTemp -2))
  {
    servoT.write(0);
    Serial.println(F("Servo is now ar position 0 (On)"));
  }
 
  // Wait for next cycle
  delay(59000);
}
