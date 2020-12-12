
#ifndef __DC_TIME_HEADER__
#define __DC_TIME_HEADER__

#include <Arduino.h>
#include <CRC32.h>

#define DC_DATAGRAM_HEADER_LEN 6

#define DC_DATAGRAM_HEADER_LEN_OFFSET 1
#define DC_DATAGRAM_HEADER_CRC_OFFSET 2

#define DC_TIME_DATAGRAM_LEN (DC_DATAGRAM_HEADER_LEN + 6)
#define DC_TIME_DATAGRAM_ID 0x20


class DCTime
{
private:
    static uint32_t calculateCRC(uint8_t *datagram);
    static void addCRC(uint8_t *datagram);
    static void buildHeader(uint8_t *datagram, uint8_t datagramId, uint8_t datagramLength);
public:
    static void buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram);    
    static void timeDatagramToString(uint8_t *datagram, char *buffer);
    static bool verifyCRC(uint8_t *datagram);
};

#endif