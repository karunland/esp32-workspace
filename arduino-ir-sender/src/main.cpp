#include <Arduino.h>

int ir_pin = 3;
long ir_val;

void sendIRValue()
{

     // start of message marker
     digitalWrite(ir_pin,HIGH);
     delay(16);
     digitalWrite(ir_pin,LOW);
     //delayMicroseconds(200);
     delay(1);
     
     for(int i=0; i<32; i++){
          int j=ir_val & 0x01;

          digitalWrite(ir_pin,HIGH);
          if(j==0){
               delay(2);
          }else{
               delay(8);
          }
          digitalWrite(ir_pin,LOW);
          //delayMicroseconds(200);
          delay(1);

          ir_val = ir_val >> 1;
     }

     // end of message marker
     digitalWrite(ir_pin,HIGH);
     delay(16);
     digitalWrite(ir_pin,LOW);
     
}

void setup() 
{
     // put your setup code here, to run once:
     Serial.begin(115200);
     Serial.println("aaa");

     // light the LED for a couple of seconds just so
     // we can see if it's working
     pinMode(ir_pin,OUTPUT);
     digitalWrite(ir_pin,HIGH);
     delay(2000);
     digitalWrite(ir_pin,LOW);
}

void loop() 
{
     // put your main code here, to run repeatedly:

     long k = random(0,256);
     long j = random(0,256);
     long     i = random(0,256);
     long h = k ^ j;
     h = h ^ i;
     Serial.print(F("sending values - k:"));
     Serial.print(k,HEX);
     Serial.print(F(" j:"));
     Serial.print(j,HEX);
     Serial.print(F(" i:"));
     Serial.print(i,HEX);     
     Serial.print(F(" checksum:"));
     Serial.print(h,HEX);
     
     k = k << 24;     
     j = j << 16;     
     i = i << 8;

     k = k | j;
     k = k | i;
     k = k | h;
     ir_val = k;

     Serial.print(F(" sent:"));
     Serial.print(ir_val,HEX);
     
     Serial.println();
     
     
     sendIRValue();

     delay(2000);
     
} 