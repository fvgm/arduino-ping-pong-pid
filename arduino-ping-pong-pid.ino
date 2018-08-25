/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
int distance = 0;
int tubeSize = 102;

int byteReceived = 0;
int pwmPin = 9;
//int deadZone = 55;
//int output = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  
  sensor.startContinuous(50);

  //sensor.setMeasurementTimingBudget(25000); // modo HIGH SPEED

  pinMode(pwmPin, OUTPUT);

}

void loop() {
   
  distance = tubeSize - (sensor.readRangeContinuousMillimeters()/10);
  Serial.write(distance); 
  
  //if (sensor.timeoutOccurred()) { 
    //Serial.println(" TIMEOUT"); 
  //}

}

void serialEvent() {
  if(Serial.available()) {
    byteReceived = Serial.read();
    analogWrite(pwmPin, byteReceived);
  }
}

