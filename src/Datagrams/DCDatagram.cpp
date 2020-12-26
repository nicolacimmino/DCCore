#include "DCDatagram.h"

void DCDatagram::buildHeader(uint8_t *datagram, uint8_t datagramId, uint8_t datagramLength)
{
    datagram[0] = datagramId;
    datagram[DC_DATAGRAM_HEADER_LEN_OFFSET] = datagramLength;
}

uint32_t DCDatagram::calculateHMAC(uint8_t *datagram)
{    
    Sha256 *sha256 = new Sha256();

    sha256->initHmac_EEPROM(DCCORE_EEPROM_HMAC_KEY, DCCORE_EEPROM_HMAC_KEY_LEN);

    for (uint8_t ix = DC_DATAGRAM_HEADER_LEN; ix < datagram[DC_DATAGRAM_HEADER_LEN_OFFSET]; ix++)
    {
        sha256->write((uint8_t)datagram[ix]);
    }

    uint8_t *hash = sha256->resultHmac();
    uint32_t hmac = hash[0] | (hash[8] << 8) | (hash[16] << 16) | (hash[24] << 24);

    delete sha256;

    return hmac;
}

void DCDatagram::addHMAC(uint8_t *datagram)
{
    uint32_t hmac = DCDatagram::calculateHMAC(datagram);

    for (uint8_t ix = DC_DATAGRAM_HEADER_HMAC_OFFSET; ix < DC_DATAGRAM_HEADER_HMAC_OFFSET + 4; ix++)
    {
        datagram[ix] = hmac & 0xFF;
        hmac = hmac >> 8;
    }
}

bool DCDatagram::verifyHMAC(uint8_t *datagram)
{
    uint32_t hmac = DCDatagram::calculateHMAC(datagram);

    for (uint8_t ix = DC_DATAGRAM_HEADER_HMAC_OFFSET; ix < DC_DATAGRAM_HEADER_HMAC_OFFSET + 4; ix++)
    {
        if (datagram[ix] != (hmac & 0xFF))
        {
            return false;
        }
        hmac = hmac >> 8;
    }

    return true;
}

bool DCDatagram::isA(uint8_t *datagram, uint8_t type)
{
    return datagram[0] == type;
}