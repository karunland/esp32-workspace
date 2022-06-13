#include <Arduino.h>
#include <IRremote.h>

unsigned char buttonstate= HIGH;

#define BUTTON 14
IRsend irsend; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:

 buttonstate = digitalRead(BUTTON);
 if (buttonstate == LOW)
 {
   Serial.println("button is pressed");
   for (int i = 0; i < 3; i++)
   {
     irsend.sendNEC(0XFFA25D, 32);
   }
   delay(500);
 }
 
}