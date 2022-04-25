#include <Arduino.h>
#include <EEPROM.h>

int writeStringToEEPROM(int, char *);
int readStringFromEEPROM(int, String *);

void setup()
{
  EEPROM.begin(50);
  Serial.begin(115200);
  // unsigned char val = 1;
  char buff[] = "hello";
  writeStringToEEPROM(0, buff);
  EEPROM.commit();
} 

void loop()
{ 

  // EEPROM.write(0, 'a');
  // EEPROM.commit();

  // uint8_t t = EEPROM.read(0);
  delay(1000);
  // Serial.printf("%d %c %u \n",t, t, t);
  String array;
  readStringFromEEPROM(0, &array);
  Serial.println(array);
}

int writeStringToEEPROM(int addrOffset, char *array)
{
  byte len = strlen(array);
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, array[i]);
  }
  return addrOffset + 1 + len;
}


int readStringFromEEPROM(int addrOffset, String *strToRead)
{
  int newStrLen = EEPROM.read(addrOffset);
  Serial.println(newStrLen);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0';
  *strToRead = String(data);
  return addrOffset + 1 + newStrLen;
}
