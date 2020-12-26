#include "DCTimeDatagram.h"

void DCTimeDatagram::buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t dayOfWeek, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram)
{
    DCTimeDatagram::buildHeader(datagram, DC_TIME_DATAGRAM_ID, DC_TIME_DATAGRAM_LEN);

    datagram[DC_DATAGRAM_HEADER_LEN] = year;
    datagram[DC_DATAGRAM_HEADER_LEN + 1] = month;
    datagram[DC_DATAGRAM_HEADER_LEN + 2] = day | (dayOfWeek << 5);
    datagram[DC_DATAGRAM_HEADER_LEN + 3] = hour;
    datagram[DC_DATAGRAM_HEADER_LEN + 4] = minute;
    datagram[DC_DATAGRAM_HEADER_LEN + 5] = second;

    DCTimeDatagram::addHMAC(datagram);
}

static uint8_t DCTimeDatagram::getYear(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN] & 0x7F;
}

static uint8_t DCTimeDatagram::getMonth(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN + 1] & 0x0F;
}

static uint8_t DCTimeDatagram::getDayOfWeek(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN + 2] >> 5;
}

static uint8_t DCTimeDatagram::getDay(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN + 2] & 0x1F;
}

static uint8_t DCTimeDatagram::getHour(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN + 3] & 0x1F;
}

static uint8_t DCTimeDatagram::getMinute(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN + 4] & 0x3F;
}

static uint8_t DCTimeDatagram::getSecond(uint8_t *datagram)
{
    return datagram[DC_DATAGRAM_HEADER_LEN + 5] & 0x3F;
}
