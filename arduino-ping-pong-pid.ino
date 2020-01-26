/* Esse código aguarda o recebimento de um byte via Serial,
que é a largura do pulso PWM. Após o recebimento deste dado, 
o código envia o valor da altura do objeto para o PC.
*/

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;
int distance = 0;
int tubeSize = 103;

int byteReceived = 0;
int pwmPin = 9;

void setup() {
  Serial.begin(9600);
  while(!Serial) {};
  
  Wire.begin();

  sensor.init();
  sensor.setTimeout(500);

  //sensor.startContinuous(50);

  sensor.setMeasurementTimingBudget(20000); // modo HIGH SPEED

  pinMode(pwmPin, OUTPUT);

  Serial.write(0); // estabelece o contato

}

void loop() {
  if (Serial.available() > 0) {
    byteReceived = Serial.read();
    
    distance = tubeSize - (sensor.readRangeSingleMillimeters()/10);  
    Serial.write(distance);
    analogWrite(pwmPin, byteReceived);
  }
}


