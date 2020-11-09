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

void setup() {
  pinMode(2, INPUT_PULLUP);

  // Begin streams
  Serial.begin(9600);
  dht.begin();
  Serial.println(F("Termostat is running!"));
}

void loop() {
  // Variables
  float currTemp;
  float calibration = 23.8 - 22.8; // DHT22 - Fluke // 2020-11-09
  sensors_event_t event;
  
  // Get temperature and print.
  dht.temperature().getEvent(&event);
  
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    currTemp = event.temperature - calibration;
    Serial.println(currTemp);
  }
  delay(5000);
}
