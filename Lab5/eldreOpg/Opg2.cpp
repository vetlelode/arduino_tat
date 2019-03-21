#include <Arduino.h>
#include <Servo.h>

Servo serv;

int const potPin = A0;
int skaler(int potVal, int skalaHoy,int vinkelHoy) {
  return potVal * (vinkelHoy/skalaHoy);
}

void formatPrint(int res, int ang) {
  char buffer [50];
  sprintf(buffer,"Resistance: %d\nAngle: %d", res, ang);
  Serial.println(buffer);
}

void setup() {
    serv.attach(9);
    Serial.begin(9600);

}
void loop() {
    int res = analogRead(potPin);
    int vinkel = skaler(res, 1023, 179);
    serv.write(vinkel);
    formatPrint(res, vinkel);
    delay(100);
}