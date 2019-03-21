#include <Arduino.h>


const int greenPin = 9;
const int redPin = 11;
const int bluePin = 10;

struct Values {
  int redVal;
  int greenVal;
  int blueVal;

  int redSensor;
  int greenSensor;
  int blueSensor;
};
Values lesAnalog(Values vals) {
  vals.redSensor = analogRead(redPin);
  delay(10);
  vals.greenSensor = analogRead(greenPin);
  delay(10);
  vals.blueSensor = analogRead(bluePin);
  delay(10);
  vals.redVal = vals.redSensor/4;
  vals.greenVal = vals.greenSensor/4;
  vals.blueVal = vals.blueSensor/4;
  return vals;
}
void printVals(Values vals) {
  char buffer [50];
  int out = sprintf(buffer,"Red sensor:%d\nGreen sensor:%d\nBlue sensor:%d\n",vals.redSensor, vals.greenSensor, vals.redSensor);
  Serial.println(buffer);
}
void analogWrite(Values vals) {
  analogWrite(redPin, vals.redVal);
  analogWrite(greenPin, vals.greenVal);
  analogWrite(bluePin, vals.blueVal);
}
void setup() {
  Serial.begin(9600);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop() {
  struct Values verdier;
  verdier = lesAnalog(verdier);
  printVals(verdier);
  delay(500);
}


