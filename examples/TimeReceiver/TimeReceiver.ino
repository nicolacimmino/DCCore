#include <DCServices.h>

DCServices *dcServices;

void setup()
{
  Serial.begin(9600);
  Serial.println("INIT");
  dcServices = new DCServices(DC_RADIO_NRF24_V3);

  // Uncomment and set your own very secret key to initialize the device EEPROM.
  // This key must match on all devices as it's used to generate and veryify datagrams HMACs.
  // uint8_t hmacKey[] = {0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
  // eeprom_write_block(hmacKey, DCCORE_EEPROM_HMAC_KEY, DCCORE_EEPROM_HMAC_KEY_LEN);
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
    //Serial.println("Error");
  }

  delete dateTime;

  //delay(200);
}