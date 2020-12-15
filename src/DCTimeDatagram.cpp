#include "DCTimeDatagram.h"

void DCTimeDatagram::buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram)
{
    DCTimeDatagram::buildHeader(datagram, DC_TIME_DATAGRAM_ID, DC_TIME_DATAGRAM_LEN);

    datagram[DC_DATAGRAM_HEADER_LEN] = year;
    datagram[DC_DATAGRAM_HEADER_LEN + 1] = month;
    datagram[DC_DATAGRAM_HEADER_LEN + 2] = day;
    datagram[DC_DATAGRAM_HEADER_LEN + 3] = hour;
    datagram[DC_DATAGRAM_HEADER_LEN + 4] = minute;
    datagram[DC_DATAGRAM_HEADER_LEN + 5] = second;

    DCTimeDatagram::addCRC(datagram);
}

