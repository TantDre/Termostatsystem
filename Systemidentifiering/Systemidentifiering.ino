/*
  ------------------------------
    System Identification (Step Response)
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
float currTemp;
float calibration = 23.10 - 22.7; // DHT - Fluke  // 2020-11-09

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

  // Add and move to off
  servoT.attach(MGPIN);
  servoT.write(180);
  delay(1000);

  // Start test
  servoT.write(0);
}

// ---------- Loop ----------
void loop() 
{
  // Get temperature
  digitalWrite(DHT5V, HIGH);
  delay(5000);
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
}
