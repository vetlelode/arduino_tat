#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
const int swiPin = 6;
int switchState = 0;
int prevSwitchState = 0;
int pos = 0;


void setup() {
    Serial.begin(9600);
    lcd.begin(16,2);
    pinMode(swiPin,INPUT);
    lcd.print("Magisk melding");
}
void loop() {
    switchState = digitalRead(swiPin);
    if(switchState != LOW) {
        prevSwitchState = switchState;
            lcd.clear();
            Serial.println(pos);
            pos++;
            if(pos <= 31){
                if(pos < 17){
                    lcd.setCursor(pos,0);
                    lcd.print("XD");
                }
                else {
                    lcd.setCursor(pos-17,1);
                    lcd.print("DX");
                }
            }
            else {
                pos = 0;
            }
        
    }
    delay(50);
}