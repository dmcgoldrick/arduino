// This is a test for the 12 pole stator compass test machine
#include <SPI.h>
#include <Wire.h>

#define hallPin A0
#define redPWM 5
#define greenPWM 3
#define bluePWM 6

// set the thresholds for blue and red triggers and green ready signal 
  const int b = 517;
  const int r = 507;
  const int g = 3;
// set a max raw value
  const int m = 865;
  
void setup() {
  Serial.begin(115200);
  pinMode(hallPin,INPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  }

void loop() {
    int bluePWMv = 0;
    int redPWMv = 0;
    int greenPWMv = 0;
    int v = analogRead(hallPin);//
    
    if (v > b) {
      bluePWMv = map(v,b,m,0,255);
      greenPWMv = 0;
      redPWMv = 0;
    }
    
    else if (v < r){
      redPWMv = map(v,0,r,255,0);
      greenPWMv = 0;
      bluePWMv = 0;
    }
    else {
    greenPWMv = g;
    }
    
    analogWrite(bluePWM, bluePWMv);
    analogWrite(redPWM, redPWMv);
    analogWrite(greenPWM, greenPWMv);

    Serial.println(v);
    Serial.println(bluePWMv);
    Serial.println(greenPWMv);
    Serial.println(redPWMv);
    Serial.println("------------");
}
