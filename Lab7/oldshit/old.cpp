const int lysPin = A2;
const int tempPin = A1;
const int hoytaler = 7;
const int rodLys = 6;
const int blaLys = 5;
const int grontLys = 4;


#include <SPI.h>
#include <Ethernet.h>

//konstanter for pinner for ryddighetenskyld

const int lysPin = A2;
const int tempPin = A1;
const int hoytaler = 7;
const int rodLys = 6;
const int blaLys = 5;
const int grontLys = 4;


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
  int mes = analogRead(lysPin);
  Serial.println(mes);
  return mes;
}

int measureTemp(){
  int mes = analogRead(tempPin);
  float voltage = (mes/1024.0) * 5.0;
  return (voltage - 0.5) * 100;
}

int makeDaBigNoize(){

}

int makeDaBigLight(){

}


void loop() {
  static int teller = 1;
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Client == true -->new client");
    boolean currentLineIsBlank = false;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' &&currentLineIsBlank){
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE html>");
          client.println("<html><body>");
          client.println("<H1>Datateknikk 2019</H1>");
          client.println("<FONT face=Verdana color= red>");
          client.println("<H2>Teller = ");
          client.println(teller);
          client.println("</H2>");
          client.println("<FONT face=Verdana color= darkblue>");
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
          client.println("<input type='submit' value='Set Frequency' />");
          client.println("</form>");
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
    /*if(client.available()){
      Serial.println("mordi");
      char c = client.read();
      bool mottar;
      if(c != ' ' && c == '?')
        mottar = true;
      else 
        mottar = false;
      if(mottar){
        
      }
    }*/
    delay(1);
    client.stop();
    Serial.println("\n\n");
  }
  teller++;
  delay(100);
}
