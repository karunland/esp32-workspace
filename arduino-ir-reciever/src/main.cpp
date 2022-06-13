#include <Arduino.h>

int ir_in = 2;
int led_pin = 13;

long int_vcc;
long min_vcc;
long mil_ir_start;
long mil_ir_end;
long mil_ir;

long ir_val;     // we'll just make this a 32-bit value
int ir_bit_count;

void parseMessage(void);
void IRLow(void);
void IRHigh(void);
void IRChange(void);


// IR high and IR low are back-to-front in the receiver.
// If we're sending IR, the sensor will be low (its an open drain collector that
// pulls an input LOW when it can see IR light) So IRLow relates to the LED being lit

void IRLow()
{
     // this fires on a high-to-low transition
     // whenever the line is pulled low it's because we're receving IR light
     // so reset the timer/counter
     mil_ir_start = millis();     
     digitalWrite(led_pin,HIGH);
}

void IRHigh()
{
     // whenever the line floats high, its because we've just turned off the IR light
     // that is sending data to the receiver, so measure the width of the last pulse
     // and do something wisth the data if necessary
     mil_ir_end = millis();
     mil_ir = mil_ir_end - mil_ir_start;
     digitalWrite(led_pin,LOW);
     
     if(mil_ir < 11){
          Serial.print(mil_ir);
          Serial.print(F("."));
     }

     // decide what to do with the pulse width
     if(mil_ir >=1 && mil_ir <=4){
          // treat this as a zero
          ir_val = ir_val << 1;
          ir_bit_count++;
          
     }else if(mil_ir >=6 && mil_ir <=12){
          // treat this as a one
          ir_val = ir_val << 1;
          ir_val = ir_val|1;          
          ir_bit_count++;
          
     }else if(mil_ir >=14 && mil_ir <=20){
          // this is a start/end message marker
          // if we've received a message, validate it and parse
          Serial.println();
          if(ir_val != 0){ parseMessage(); }
          
          // now reset everything ready for the next blast
          ir_bit_count = 0;
          ir_val = 0;
     
     }

     
}

void parseMessage()
{
     // a message can be up to three bytes long
     // we'll do simple XOR checksum on the fourth byte
     // and squash them all together

     int a = ir_val >> 24;
     int b = ir_val >> 16;
     int c = ir_val >> 8;
     int d = ir_val & 255;

     a = a & 0xFF;
     b = b & 0xFF;
     c = c & 0xFF;
     d = d & 0xFF;

     int k = a ^ b;
     k = k ^ c;
     if(k==d){
          // checksum success
          Serial.print(F("Received: "));
          Serial.print(ir_val,HEX);
          Serial.println();
          
     }else{
          // checksum fail
          Serial.print(F("checksum fail a:"));
          Serial.print(a,HEX);
          Serial.print(F(" b:"));
          Serial.print(b,HEX);
          Serial.print(F(" c:"));
          Serial.print(c,HEX);
          Serial.print(F(" d:"));
          Serial.print(d,HEX);
          Serial.println(F(" "));
          
     }
     
}

void IRChange()
{
     int b = digitalRead(ir_in);
     if(b==HIGH){ IRHigh(); } else { IRLow();}
}

void setup() {
     // put your setup code here, to run once:
     Serial.begin(9600);

     pinMode(led_pin,OUTPUT);
     pinMode(ir_in,INPUT_PULLUP);

     // create an interrupt on pin 2 (IR receiver)
     attachInterrupt(digitalPinToInterrupt(ir_in), IRChange, CHANGE);
     
}

void loop() {
     // put your main code here, to run repeatedly:
     
     delay(1000);
     
} 