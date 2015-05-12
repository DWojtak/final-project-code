#include <SPI.h>        
#include <Ethernet.h>
#include <EthernetUdp.h>
byte mac[] = {   0x90, 0xA2, 0xDA, 0x00, 0x78, 0x19 };
IPAddress ip(192,168,1,149);
unsigned int localPort = 5005;      
IPAddress RemIP(192,168,1,100);
unsigned int RemPort = 5005;
EthernetUDP Udp;
String hxdata = "";
String rxdata = "";
char endpack ='\n';
String red, green, blue;
String redv, greenv, bluev, hexv;
String hexcol;
int x = 0;

void setup() {
    Ethernet.begin(mac,ip);
    Udp.begin(localPort);
    Serial.begin(9600);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(9, INPUT);
}

void loop() {
    while (Serial.available()) {
        int ch = Serial.read();
        if (ch == -1) {
          
        }
        else if (ch == endpack) {
            break;
            delay(50);
        }       
        else {
            rxdata += (char) ch;
            delay(50);
        }       
    }

  if (rxdata[0] == 'r'){
    red = rxdata;

  }
  else if (rxdata[0] == 'g'){
    green = rxdata;

  }
  else if (rxdata[0] == 'b'){
    blue = rxdata;

  }
  else if (rxdata[0] == 'h'){
    hexcol = rxdata;

  }
  else{

  }
  rxdata = "";
  hxdata = "";
  redv = red.substring(1,4); 
  greenv = green.substring(1,4); 
  bluev = blue.substring(1,4); 
  hexv = hexcol.substring(1,7);
  Serial.println(redv);
  Serial.println(greenv);
  Serial.println(bluev);
  Serial.println(hexv);
  analogWrite(5, redv.toInt());   //5 red 6 blue 9 green
  analogWrite(6, bluev.toInt());
  analogWrite(9, greenv.toInt());
  x++;
  if (x == 20){
   Udp.beginPacket(RemIP, RemPort);
   Udp.print(hexv); 
   Udp.endPacket();
   x=0;

 }
}
