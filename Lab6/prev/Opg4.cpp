#include <Arduino.h>
#define C1 260 
#define D 292
#define E 328
#define F 348
#define G 392
#define A 440
#define H 492
#define C2 520

int i = 0;

void setup(){
    Serial.begin(9600);
    pinMode(12, OUTPUT);
}
void loop(){
    int melodi1[22]= {C1,D,E,F,G,G,A,A,A,A,G,F,F,F,F,E,E,D,D,D,D,C2};
    int varighet1[22] = {1,1,1,1,2,2,1,1,1,1,4,1,1,1,1,2,2,1,1,1,1,4};
    Serial.println(melodi1[i]);
    tone(12, melodi1[i], varighet1[i] * 500);
    if(i <= 8)
        i++;
    else 
        i = 0;
    delay(varighet1[i]* 500 + 10);
}