#include <Arduino.h>
#include <dc_time.h>
#include <CRC32.h>

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  uint8_t datagram[DC_TIME_DATAGRAM_LEN];
  DCTime::buildTimeDatagram(10, 22, (millis() / 1000) % 60, 11, 12, 20, datagram);

  for (uint8_t ix = 0; ix < datagram[DC_DATAGRAM_HEADER_LEN_OFFSET]; ix++)
  {
    Serial.print(datagram[ix], HEX);
    Serial.print(".");
  }

  Serial.print(" - ");

  if (DCTime::verifyCRC(datagram))
  {
    Serial.println(" CRC OK");
  }
  else
  {
    Serial.println(" CRC ERR");
  }

  char buffer[32];
  memset(buffer, 0, 32);

  DCTime::timeDatagramToString(datagram, buffer);

  Serial.println(buffer);

  delay(1000);
}