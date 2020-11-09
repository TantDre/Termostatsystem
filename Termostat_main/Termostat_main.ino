// Includes Temperature
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Inculdes Servo
#include <Servo.h>

// DHT Setup
#define DHTPIN 2
#define DHTTYPE DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

// ----- Setup -----
void setup() 
{
  // Pullup resistor for data signal
  pinMode(2, INPUT_PULLUP);

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
  dht.temperature().getEvent(&event);

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
  delay(5000);
}
