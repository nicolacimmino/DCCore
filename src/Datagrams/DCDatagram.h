
#ifndef __DC_DATAGRAM_HEADER__
#define __DC_DATAGRAM_HEADER__

#include <Arduino.h>
#include "../sha256.h"

#define DCCORE_EEPROM_VSIM_BASE 0
#define DCCORE_EEPROM_VSIM_LEN 10
#define DCCORE_EEPROM_HMAC_KEY 1
#define DCCORE_EEPROM_HMAC_KEY_LEN 8
#define DC_DATAGRAM_HEADER_LEN 6

#define DC_DATAGRAM_HEADER_ID_OFFSET 0
#define DC_DATAGRAM_HEADER_LEN_OFFSET 1
#define DC_DATAGRAM_HEADER_HMAC_OFFSET 2


class DCDatagram
{
protected:
    static uint32_t calculateHMAC(uint8_t *datagram);
    static void addHMAC(uint8_t *datagram);
    static void buildHeader(uint8_t *datagram, uint8_t datagramId, uint8_t datagramLength);
public:
    static bool verifyHMAC(uint8_t *datagram);
    static bool isA(uint8_t *datagram, uint8_t type);
};

#endif