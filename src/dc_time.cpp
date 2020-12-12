#include "dc_time.h"

void DCTime::buildTimeDatagram(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t month, uint8_t year, uint8_t *datagram)
{
    DCTime::buildHeader(datagram, DC_TIME_DATAGRAM_ID, DC_TIME_DATAGRAM_LEN);

    datagram[DC_DATAGRAM_HEADER_LEN] = hour;
    datagram[DC_DATAGRAM_HEADER_LEN + 1] = minute;
    datagram[DC_DATAGRAM_HEADER_LEN + 2] = second;
    datagram[DC_DATAGRAM_HEADER_LEN + 3] = day;
    datagram[DC_DATAGRAM_HEADER_LEN + 4] = month;
    datagram[DC_DATAGRAM_HEADER_LEN + 5] = year;

    DCTime::addCRC(datagram);
}

void DCTime::buildHeader(uint8_t *datagram, uint8_t datagramId, uint8_t datagramLength)
{
    datagram[0] = datagramId;
    datagram[DC_DATAGRAM_HEADER_LEN_OFFSET] = datagramLength;
}

uint32_t DCTime::calculateCRC(uint8_t *datagram)
{
    CRC32 crc;
    for (uint8_t ix = DC_DATAGRAM_HEADER_LEN; ix < datagram[DC_DATAGRAM_HEADER_LEN_OFFSET]; ix++)
    {
        crc.update(datagram[ix]);
    }

    return crc.finalize();
}

void DCTime::addCRC(uint8_t *datagram)
{
    uint32_t checksum = DCTime::calculateCRC(datagram);

    for (uint8_t ix = DC_DATAGRAM_HEADER_CRC_OFFSET; ix < DC_DATAGRAM_HEADER_CRC_OFFSET + 4; ix++)
    {
        datagram[ix] = checksum & 0xFF;
        checksum = checksum >> 8;
    }
}

bool DCTime::verifyCRC(uint8_t *datagram)
{
    CRC32 crc;
    for (uint8_t ix = DC_DATAGRAM_HEADER_LEN; ix < datagram[DC_DATAGRAM_HEADER_LEN_OFFSET]; ix++)
    {
        crc.update(datagram[ix]);
    }

    uint32_t checksum = crc.finalize();

    for (uint8_t ix = DC_DATAGRAM_HEADER_CRC_OFFSET; ix < DC_DATAGRAM_HEADER_CRC_OFFSET + 4; ix++)
    {
        if (datagram[ix] != (checksum & 0xFF))
        {
            return false;
        }
        checksum = checksum >> 8;
    }

    return true;
}
