// Includes Temperature
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Inculdes Servo
#include <Servo.h>

// DHT Setup
#define DHTPIN 12
#define DHT5V 13
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// ----- Setup -----
void setup() 
{
  // Pullup resistor for data signal
  pinMode(DHTPIN, INPUT_PULLUP);

  // 5V Pin to Sensor
  pinMode(DHT5V, OUTPUT);

  // Begin streams
  Serial.begin(9600);
  dht.begin();

  // Init print
  Serial.println(F("Termostat is now running:"));
}

// ----- Loop -----
void loop() 
{
  // Variables
  float currTemp;
  sensors_event_t event;

  // Calibration (DHT22 - Fluke)
  float calibration = 23.8 - 22.8;  // 2020-11-09
  
  // Get temperature
  digitalWrite(DHT5V, HIGH);
  delay(1000);
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

  // Wait for next cycle
  delay(4000);
}
