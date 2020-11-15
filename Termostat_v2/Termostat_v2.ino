/*
  ------------------------------
    Thermostat Control System
    Verision: 2.0
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

// PID
float acc_error = 0;
float prev_error = 0;
float Ts = 1; 

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

// ---------- PID Controller ----------
float PID()
{ 
  // Variables
  float u, e, kp, ki, kd, In, v, P, I, D;
  kp = 0.1;
  ki = 0.01;
  kd = 0.001;

  // Error
  e = refTemp - currTemp;

  // PID
  P = kp * e;
  I = acc_error + ki * Ts * e;
  D = kd * (e - prev_error)/Ts;
  v = P + I + D;

  // Saturation
  if (v < 0)
  {
    u = 0;
    In = acc_error;
    
  } else if (v > 1)
  {
    u = 1;
    In = acc_error;
  } else
  {
    u = v;
    In = I;
  }

  // Anti Windup
  acc_error = In + Ts * (u - v) * kp / ki;

  // Return
  return u;
}

// ---------- Loop ----------
void loop() 
{
  // Get temperature
  digitalWrite(DHT5V, HIGH);
  delay(Ts*1000);
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

  // Control
  int servoAngle = map(PID(), 0, 1, 180, 0);

  // Move Servo
  servoT.write(servoAngle);
  Serial.println(servoAngle); 
   
}
