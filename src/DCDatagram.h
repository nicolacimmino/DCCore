
#ifndef __DC_DATAGRAM_HEADER__
#define __DC_DATAGRAM_HEADER__

#include <Arduino.h>
#include <CRC32.h>

#define DC_DATAGRAM_HEADER_LEN 6

#define DC_DATAGRAM_HEADER_LEN_OFFSET 1
#define DC_DATAGRAM_HEADER_CRC_OFFSET 2


class DCDatagram
{
protected:
    static uint32_t calculateCRC(uint8_t *datagram);
    static void addCRC(uint8_t *datagram);
    static void buildHeader(uint8_t *datagram, uint8_t datagramId, uint8_t datagramLength);
public:
    static bool verifyCRC(uint8_t *datagram);
};

#endif