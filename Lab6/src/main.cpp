#include <Arduino.h>

 
void setup() {
    Serial.begin(9600);
    pinMode(2, INPUT);
    pinMode(9,  OUTPUT);
}
 
void loop() {
    Serial.println(digitalRead(2));
    if (digitalRead(2) != 0 ) {
        digitalWrite(9, HIGH);
        delay(100);
    } else {
        digitalWrite(9, LOW);
        delay(100);        
    }

}