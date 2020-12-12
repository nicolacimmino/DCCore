#include "dc_time.h"

void DCTime::buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram)
{
    datagram[0] = DC_TIME_DATAGRAM_ID;
    datagram[1] = hour;
    datagram[2] = minute;
    datagram[3] = second;
    datagram[4] = day;
    datagram[5] = month;
    datagram[6] = year;

    DCTime::appendCRC(datagram, 7);
}

void DCTime::appendCRC(uint8_t *datagram, uint8_t crcStartOffset)
{
    CRC32 crc;
    for (uint8_t ix = 0; ix < crcStartOffset; ix++)
    {
        crc.update(datagram[ix]);
    }

    uint32_t checksum = crc.finalize();

    for (uint8_t ix = crcStartOffset; ix < crcStartOffset + 4; ix++)
    {
        datagram[ix] = checksum & 0xFF;
        checksum = checksum >> 8;
    }
}

bool DCTime::verifyCRC(uint8_t *datagram, uint8_t datagramLength)
{
  CRC32 crc;
  for (uint8_t ix = 0; ix < datagramLength - 4; ix++)
  {
    crc.update(datagram[ix]);
  }

  uint32_t checksum = crc.finalize();
  
  for (uint8_t ix = datagramLength - 4; ix < datagramLength; ix++)
  {
    if (datagram[ix] != (checksum & 0xFF))
    {
      return false;
    }
    checksum = checksum >> 8;
  }

  return true;
}
