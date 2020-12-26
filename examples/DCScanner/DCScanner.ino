#include <DCServices.h>

DCServices *dcServices;

void setup()
{
  Serial.begin(9600);
  dcServices = new DCServices(DC_RADIO_NRF24_V3);
}

void loop()
{
  uint8_t datagram[64];

  if (dcServices->receiveRawDatagram(TIME_BROADCAST_CHANNEL, datagram, 64))
  {
    for (uint8_t ix = 0; ix < datagram[DC_DATAGRAM_HEADER_LEN_OFFSET]; ix++)
    {
      Serial.print("0123456789ABCDEF"[datagram[ix] >> 4]);
      Serial.print("0123456789ABCDEF"[datagram[ix] & 0x0F]);
      Serial.print(".");
    }
    Serial.println("");
  }
}