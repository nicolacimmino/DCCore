
#ifndef __DC_TIME_HEADER__
#define __DC_TIME_HEADER__

#include <Arduino.h>
#include <CRC32.h>

#define DC_TIME_DATAGRAM_LEN 11
#define DC_TIME_DATAGRAM_ID 0x20


class DCTime
{
private:
    static void appendCRC(uint8_t *datagram, uint8_t crcStartOffset);
public:
    static void buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram);    
    static bool verifyCRC(uint8_t *datagram, uint8_t datagramLength);
};

#endif