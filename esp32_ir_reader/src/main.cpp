#include <Arduino.h>

// Include IR Remote Library by Ken Shirriff
#include <IRremote.h>
 
// Define sensor pin
const int RECV_PIN = 4;
 
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;
 
 
void setup(){
  // Serial Monitor @ 115200 baud
  Serial.begin(115200);
  // Enable the IR Receiver
  irrecv.enableIRIn();
}
 
void loop(){
  if (irrecv.decode(&results)){
    // Print Code in HEX
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}