#include <Arduino.h>

//*****************************************
// NEC (Japanese) Infrared code sending library for the Arduino
// Send a standard NEC 4 byte protocol direct to an IR LED on the define pin
// Assumes an IR LED connected on I/O pin to ground, or equivalent driver.
// Tested on a Freetronics Eleven Uno compatible
// Written by David L. Jones www.eevblog.com
// Youtube video explaining this code: http://www.youtube.com/watch?v=BUvFGTxZBG8
// License: Creative Commons CC BY
//*****************************************

#define IRLEDpin  3              //the arduino pin connected to IR LED to ground. HIGH=LED ON
#define BITtime   562            //length of the carrier bit in microseconds
//put your own code here - 4 bytes (ADDR1 | ADDR2 | COMMAND1 | COMMAND2)
unsigned long IRcode=0b11000001110001111100000000111111;  
// unsigned long IRcode=0xffaa;  

// SOME CODES:
// Canon WL-D89 video remote START/STOP button = 0b11000001110001111100000000111111

void setup()
{
}

void IRsetup(void)
{
  pinMode(IRLEDpin, OUTPUT);
  digitalWrite(IRLEDpin, LOW);    //turn off IR LED to start
}

// Ouput the 38KHz carrier frequency for the required time in microseconds
// This is timing critial and just do-able on an Arduino using the standard I/O functions.
// If you are using interrupts, ensure they disabled for the duration.
void IRcarrier(unsigned int IRtimemicroseconds)
{
  for(int i=0; i < (IRtimemicroseconds / 26); i++)
    {
    digitalWrite(IRLEDpin, HIGH);   //turn on the IR LED
    //NOTE: digitalWrite takes about 3.5us to execute, so we need to factor that into the timing.
    delayMicroseconds(9);          //delay for 13us (9us + digitalWrite), half the carrier frequnecy
    digitalWrite(IRLEDpin, LOW);    //turn off the IR LED
    delayMicroseconds(9);          //delay for 13us (9us + digitalWrite), half the carrier frequnecy
    }
}

//Sends the IR code in 4 byte NEC format
void IRsendCode(unsigned long code)
{
  //send the leading pulse
  IRcarrier(9000);            //9ms of carrier
  delayMicroseconds(4500);    //4.5ms of silence
  
  //send the user defined 4 byte/32bit code
  for (int i=0; i<32; i++)            //send all 4 bytes or 32 bits
    {
    IRcarrier(BITtime);               //turn on the carrier for one bit time
    if (code & 0x80000000)            //get the current bit by masking all but the MSB
      delayMicroseconds(3 * BITtime); //a HIGH is 3 bit time periods
    else
      delayMicroseconds(BITtime);     //a LOW is only 1 bit time period
     code<<=1;                        //shift to the next bit for this byte
    }
  IRcarrier(BITtime);                 //send a single STOP bit.
}

void loop()                           //some demo main code
{
  IRsetup();                          //Only need to call this once to setup
  
  while(1)
  {
    IRsendCode(IRcode);                 
    delay(2000);
    IRsendCode(IRcode);
  }
}