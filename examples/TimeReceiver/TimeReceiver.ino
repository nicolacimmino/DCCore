#include <DCServices.h>

DCServices *dcServices;

void setup()
{
  Serial.begin(9600);
  dcServices = new DCServices(DC_RADIO_NRF24_V2);
}

void loop()
{
  if(dcServices->syncRTCToTimeBroadcast())
  {
    Serial.println("Sync OK");
  }

  delay(1000);
}