#include <Arduino.h>
#include <DCDatagrams.h>
#include <probo.h>

void setup()
{
    Serial.begin(9600);

    proboInit(&Serial, false);
}

void testTimeDatagramIsValid()
{
    startTest("Should build a valid time datagram");

    // Arrage
    uint8_t datagram[64];
    uint8_t expectedDatagram[] = {32, 12, 113, 171, 18, 102, 20, 12, 11, 10, 22, 33};

    // Act
    DCTimeDatagram::buildTimeDatagram(10, 22, 33, 11, 12, 20, datagram);

    // Assert
    proboAssertTrue(DCTimeDatagram::verifyCRC(datagram), "CRC Valid");
    proboAssertBuffersEqual(expectedDatagram, datagram, DC_TIME_DATAGRAM_LEN , "Datagram");
}

void testInvalidCRCShouldFail()
{
    startTest("Should fail validating a CRC");

    // Arrage
    uint8_t datagram[64];
    uint8_t testDatagram[] = {32, 12, 110, 171, 18, 102, 20, 12, 11, 10, 22, 33};

    // Act
    bool crcValid = DCTimeDatagram::verifyCRC(testDatagram);

    // Assert
    proboAssertFalse(crcValid, "CRC invalid");
}

void loop()
{
    testInvalidCRCShouldFail();
    testTimeDatagramIsValid();
    proboFinalise();

    while (1)
        ;
}