#include <Arduino.h>

void format(int res) {
  char buffer [50];
  sprintf(buffer,"Res:%d \n", res);
  Serial.println(buffer);

}

void setup() {
    Serial.begin(9600);
    
}
void loop() {
    int res = analogRead(A0);
    format(res);
    if(res >= 1023) {
        tone(8, 262, 100);
    }
    else if (res >= 990 && res <= 1010) {
        tone(8, 294, 100);
    }
    else if (res >= 505 && res <= 515) {
        tone(8, 330, 100);
    }
    else if (res >= 5 && res <= 10) {
        tone(8, 349, 100);
    }
    else if (res == 1000) {
        tone(8, 440, 100);
    }
    delay(500);

}