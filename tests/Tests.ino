#include <Arduino.h>
#include <DCServices.h>
#include <probo.h>

void setup()
{
    Serial.begin(9600);

    proboInit(&Serial, false);
}

void validateVSim()
{
    uint8_t expectedVSim[] = {0x00, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x01};
    uint8_t actualVSim[DCCORE_EEPROM_VSIM_LEN];

    eeprom_read_block(actualVSim, DCCORE_EEPROM_VSIM_BASE, DCCORE_EEPROM_VSIM_LEN);

    proboAssertBuffersEqual(expectedVSim, actualVSim, DCCORE_EEPROM_VSIM_LEN, "vSIM");
}

void testTimeDatagramIsValid()
{
    startTest("Should build a valid time datagram");

    // Arrage
    uint8_t datagram[64];
    uint8_t expectedDatagram[] = {32, 12, 216, 43, 81, 136, 20, 12, 43, 10, 22, 33};

    // Act
    DCTimeDatagram::buildTimeDatagram(10, 22, 33, 1, 11, 12, 20, datagram);

    // Assert
    proboAssertTrue(DCTimeDatagram::verifyHMAC(datagram), "HMAC Valid");
    proboAssertBuffersEqual(expectedDatagram, datagram, DC_TIME_DATAGRAM_LEN, "Datagram");
}

void testInvalidCRCShouldFail()
{
    startTest("Should fail validating a HMAC");

    // Arrage
    uint8_t datagram[64];
    uint8_t testDatagram[] = {32, 12, 110, 171, 18, 102, 20, 12, 11, 10, 22, 33};

    // Act
    bool crcValid = DCTimeDatagram::verifyHMAC(testDatagram);

    // Assert
    proboAssertFalse(crcValid, "HMAC invalid");
}

void loop()
{
    // Preconditions
    validateVSim();

    // Actual tests
    testInvalidCRCShouldFail();
    testTimeDatagramIsValid();
    proboFinalise();

    while (1)
        ;
}