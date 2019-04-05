#include <Arduino.h>

int pin = 9;
int counter = 0;
bool flip = false;
bool poll = false;
unsigned long msec = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}
void reset(){
  poll = false;
  msec = millis();
}

void interrupt(uint8_t read){
  if(read != 0 && pin <= 10)
    pin++;
  else
    pin = 9;
  reset();
}


void loop() {
  analogWrite(9, LOW);
  analogWrite(10, LOW);
  analogWrite(11, LOW);
  analogWrite(pin, counter);
  if(!flip)
    counter++;
  else 
    counter--;
  
  if(counter > 255 || counter <= 0)
    flip = !flip;
  if(digitalRead(2) != 0 && !poll){
    msec = millis();
    poll = true;
  }
  else if(poll && digitalRead(2) != 0){
    Serial.println(millis() - msec);
    if(millis() - msec > 500){
      interrupt(digitalRead(2));
    }
    else{
      return;
    }
  }
  else if(digitalRead(2) == 0){
    reset();
  }
  delay(10);
}

