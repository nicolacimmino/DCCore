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
  DCTime::buildTimeDatagram(10, 22, 33, 11, 12, 20, datagram);

  for (uint8_t ix = 0; ix < DC_TIME_DATAGRAM_LEN; ix++)
  {
    Serial.print(datagram[ix], HEX);
    Serial.print(".");
  }

  Serial.print(" - ");

  if (DCTime::verifyCRC(datagram, DC_TIME_DATAGRAM_LEN))
  {
    Serial.println(" CRC OK");
  }
  else
  {
    Serial.println(" CRC ERR");
  }

  delay(1000);
}