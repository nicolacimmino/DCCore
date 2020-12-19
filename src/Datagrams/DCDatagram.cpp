#include "DCDatagram.h"

void DCDatagram::buildHeader(uint8_t *datagram, uint8_t datagramId, uint8_t datagramLength)
{
    datagram[0] = datagramId;
    datagram[DC_DATAGRAM_HEADER_LEN_OFFSET] = datagramLength;
}

uint32_t DCDatagram::calculateCRC(uint8_t *datagram)
{
    CRC32 crc;
    for (uint8_t ix = DC_DATAGRAM_HEADER_LEN; ix < datagram[DC_DATAGRAM_HEADER_LEN_OFFSET]; ix++)
    {
        crc.update(datagram[ix]);
    }

    return crc.finalize();
}

void DCDatagram::addCRC(uint8_t *datagram)
{
    uint32_t checksum = DCDatagram::calculateCRC(datagram);

    for (uint8_t ix = DC_DATAGRAM_HEADER_CRC_OFFSET; ix < DC_DATAGRAM_HEADER_CRC_OFFSET + 4; ix++)
    {
        datagram[ix] = checksum & 0xFF;
        checksum = checksum >> 8;
    }
}

bool DCDatagram::verifyCRC(uint8_t *datagram)
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

bool DCDatagram::isA(uint8_t *datagram, uint8_t type)
{
    return datagram[0] == type;
}