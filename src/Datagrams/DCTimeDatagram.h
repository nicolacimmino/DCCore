
#ifndef __DC_TIME_HEADER__
#define __DC_TIME_HEADER__

#include "DCDatagram.h"

#define DC_TIME_DATAGRAM_LEN (DC_DATAGRAM_HEADER_LEN + 6)
#define DC_TIME_DATAGRAM_ID 0x20

class DCTimeDatagram : public DCDatagram
{
public:
    static void buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t dayOfWeek, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram);
    static uint8_t getYear(uint8_t *datagram);
    static uint8_t getMonth(uint8_t *datagram);
    static uint8_t getDayOfWeek(uint8_t *datagram);
    static uint8_t getDay(uint8_t *datagram);
    static uint8_t getHour(uint8_t *datagram);
    static uint8_t getMinute(uint8_t *datagram);
    static uint8_t getSecond(uint8_t *datagram);
};

#endif