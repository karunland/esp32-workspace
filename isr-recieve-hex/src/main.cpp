#include <Arduino.h>
#include <IRremote.h>

int IRSensor = 7; // connect ir sensor module to Arduino pin 9

int LED = LED_BUILTIN; // conect LED to Arduino pin 13

void setup()

{

  Serial.begin(115200); // Init Serila at 115200 Baud

  Serial.println("Serial Working"); // Test to check if serial is working or not

  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT

  pinMode(LED, OUTPUT); // LED Pin Output

}

void loop()

{

  int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input

  if (sensorStatus == 1) // Check if the pin high or not

  {

    // if the pin is high turn off the onboard Led

    digitalWrite(LED, LOW); // LED LOW

    Serial.println("Motion Ended!"); // print Motion Detected! on the serial monitor window

  }

  else

  {

    //else turn on the onboard LED

    digitalWrite(LED, HIGH); // LED High

    Serial.println("Motion Detected!"); // print Motion Ended! on the serial monitor window

  }
  delay(500);
}


/*

#include <IRremote.h>

const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  }
}*/
