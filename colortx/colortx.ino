#include <Wire.h>
#include "Adafruit_TCS34725.h"

char packend ='\n';
uint16_t clear, red, green, blue;
String hexcol;

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
#define commonAnode true
byte gammatable[256];

void setup() {
  Serial.begin(9600);
  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }
  
    for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
  }
}

void loop() {
  tcs.getRawData(&red, &green, &blue, &clear);

  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;  

  Serial.print("r");
  Serial.print(gammatable[(int)r]);
  Serial.println(packend);
  delay(50);
  Serial.print("g");
  Serial.print(gammatable[(int)g]);
  Serial.println(packend);
  delay(50);
  Serial.print("b");
  Serial.print(gammatable[(int)b]);
  Serial.println(packend);
  delay(50);
  Serial.print("h");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println(packend);
  delay(500);
 
}
