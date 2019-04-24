#include <SPI.h>
#include <Ethernet.h>

//konstanter for pinner for ryddighetenskyld

const int lysPin = A2;
const int tempPin = A1;
const int hoytaler = 7;
const int rodLys = 3;
const int blaLys = 5;
const int grontLys = 4;
bool maal = true;

byte mac[] = {0x90, 0xA2, 0xDA, 0x0F, 0x60, 0x9F};
IPAddress ip(192, 168, 1, 69);
EthernetServer server(80);
void setup() {
  pinMode(grontLys, OUTPUT);
  analogWrite(grontLys, HIGH);
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
  }
  Ethernet.begin(mac, ip);
  delay(1000);
  server.begin();
  Serial.print("server is at: ");
  Serial.println(Ethernet.localIP());
  Serial.println("End setup()");
}


int measureLys(){
  if(!maal)
    return 0;
  int mes = analogRead(lysPin);
  Serial.println(mes);
  return mes;
}

int measureTemp(){
  if(!maal)
    return 0;
  int mes = analogRead(tempPin);
  float voltage = (mes/1024.0) * 5.0;
  return (voltage - 0.5) * 100;
}

int makeDaBigNoize(){
  return 0;
}

int makeDaBigLight(){
  return 0;
}


void loop() {
  String msg;
  bool lys1, lys2;
  int freq;
  static int teller = 1;
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = false;
    while (client.connected()) {
      if (client.available()) {
        digitalWrite(grontLys, HIGH);
        char c = client.read();
        msg += c;
        if (c == '\n' &&currentLineIsBlank){
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 20");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html><body style='font-family: Arial, Helvetica, sans-serif;'>");
          client.println("<meta charset='UTF-8'>");
          client.println("<H1>Andrea og Vetles lab7 😎</H1>");
          client.println("<H2>Teller = ");
          client.println(teller);
          client.println("</H2>");
          client.println("<p style='color:#333'>Temperatur:");
          client.println(measureTemp());
          client.println("</p>");
          client.println("<p style='color:#333'>Lysstyrke");
          client.println(measureLys());
          client.println("</p>");
          client.println("<br><br>");
          client.println("<form action='' method='get'>");
          client.print("<input type='range' name='S' min='0' "
                       "max='2000'step='100' value='0'/>");
          client.println("<br><input type='checkbox' name='R'/> Rød");
          client.println("<input type='checkbox' name='M'/> Blå");
          client.println("<input type='checkbox' name='U' checked/> Mål (av/på) ");
          client.println("<br><input type='submit' value='Set Frequency' />");
          client.println("</form><br>");
          client.println("</body></html>");
          break;
        }
        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        } 
      }
      
    }
    digitalWrite(grontLys, LOW);
    Serial.println(msg);
    lys1, lys2 = false;
    /*
        Hent ut selve url parameteret fra GET requesten.
    */
    if(msg.indexOf("S") != 0){
      String param = "";
      int pos = msg.indexOf("S");
      int len = msg.length();
      for(int i = 1; i <= 6; i++){
         if(msg.charAt(pos + i + 1) != ' ')
            param += msg.charAt(pos + i + 1);
      }
      freq = param.toInt();
    }
    /*
      For den røde lyspæra
    */
    if(msg.indexOf("R") != 0){
      String param = "";
      int pos = msg.indexOf("R");
      int len = msg.length();

      for(int i = 1; i <= 2; i++){
         if(msg.charAt(pos + i + 1) != ' ')
            param += msg.charAt(pos + i + 1);
      }
      Serial.println(param);
      if(param == "on")
        lys1 = true;
      else 
        lys1 = false;
    }

    /*
      For den blå lyspæra
    */
    if(msg.indexOf("M") != 0){
      String param = "";
      int pos = msg.indexOf("M");
      int len = msg.length();

      for(int i = 1; i <= 2; i++){
         if(msg.charAt(pos + i + 1) != ' ')
            param += msg.charAt(pos + i + 1);
      }
      Serial.println(param);
      if(param == "on")
        lys2 = true;
      else 
        lys2 = false;
    }
    /*
      For å måle alt
    */
    if(msg.indexOf("U") != 0){
      String param = "";
      int pos = msg.indexOf("U");
      int len = msg.length();

      for(int i = 1; i <= 2; i++){
         if(msg.charAt(pos + i + 1) != ' ')
            param += msg.charAt(pos + i + 1);
      }
      Serial.println(param);
      if(param == "on")
        maal = true;
      else 
        maal = false;
    }
    delay(1);
    client.stop();
  }
  tone(7, freq, 400);
  if(lys1)
    analogWrite(rodLys, HIGH);
  else
    analogWrite(rodLys, LOW);
  if(lys2)
    analogWrite(blaLys, HIGH);
  else
    analogWrite(blaLys, LOW);
  
  teller++;
  delay(300);
}
