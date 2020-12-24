#include <DCServices.h>

DCServices *dcServices;

void setup()
{
  Serial.begin(9600);
  dcServices = new DCServices(DC_RADIO_NRF24_V3);
}

void loop()
{
  DateTime *dateTime = new DateTime();

  if (dcServices->receiveTimeBroadcast(dateTime))
  {
    char buf[64];
    sprintf(buf, "20%02d%02d%02dT%02d:%02d:%02d",        
        dateTime->year,
        dateTime->month,
        dateTime->day,                
        dateTime->hour,
        dateTime->minute,
        dateTime->second
        );
    Serial.println(buf);
  }
  else
  {
    Serial.println("Error");
  }

  delete dateTime;

  delay(200);
}