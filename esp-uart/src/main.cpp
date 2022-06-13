#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.printf("hello from esp32\r\n");
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(250);
}