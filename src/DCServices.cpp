#include "DCServices.h"

/**
 * Constructor.
 * 
 * Parameters:
 * radioType    Radio harware type as declared in RadioDriver.h DC_RADIO_xxxx
 */
DCServices::DCServices(uint8_t radioType, uRTCLib *rtc = NULL)
{
    this->radio = RadioDriverFactory::createRadio(radioType);
    radio->setRXExtendedPreamble(DC_SERVICES_EXTENDED_PREAMBLE);
    radio->setTXExtendedPreamble(DC_SERVICES_EXTENDED_PREAMBLE);
    radio->setTXPower(3);

    this->rtc = rtc;
}

void DCServices::broadcastTime()
{
    uint8_t datagram[DC_TIME_DATAGRAM_LEN];

    this->rtc->refresh();
    DCTimeDatagram::buildTimeDatagram(
        this->rtc->hour(),
        this->rtc->minute(),
        this->rtc->second(),
        this->rtc->dayOfWeek(),
        this->rtc->day(),
        this->rtc->month(),
        this->rtc->year(),
        datagram);

    this->radio->setRFChannel(TIME_BROADCAST_CHANNEL);
    this->radio->send(datagram, DC_TIME_DATAGRAM_LEN);
}

bool DCServices::syncRTCToTimeBroadcast()
{
    if (this->rtc == NULL)
    {
        return false;
    }

    DateTime *dateTime = new DateTime();
    bool success = false;

    if (this->receiveTimeBroadcast(dateTime))
    {
        this->rtc->set(
            dateTime->second,
            dateTime->minute,
            dateTime->hour,
            dateTime->dayOfWeek,
            dateTime->day,
            dateTime->month,
            dateTime->year);

        success = true;
    }

    delete dateTime;

    return success;
}

bool DCServices::receiveTimeBroadcast(DateTime *dateTime)
{
    uint8_t datagram[DC_TIME_DATAGRAM_LEN];

    this->radio->setRFChannel(TIME_BROADCAST_CHANNEL);

    if (this->radio->receive(datagram, DC_TIME_DATAGRAM_LEN, 1000))
    {
        if (!DCDatagram::verifyHMAC(datagram) || !DCDatagram::isA(datagram, DC_TIME_DATAGRAM_ID))
        {
            return false;
        }

        dateTime->second = DCTimeDatagram::getSecond(datagram);
        dateTime->minute = DCTimeDatagram::getMinute(datagram);
        dateTime->hour = DCTimeDatagram::getHour(datagram);
        dateTime->dayOfWeek = DCTimeDatagram::getDayOfWeek(datagram);
        dateTime->day = DCTimeDatagram::getDay(datagram);
        dateTime->month = DCTimeDatagram::getMonth(datagram);
        dateTime->year = DCTimeDatagram::getYear(datagram);

        return true;
    }

    return false;
}

bool DCServices::receiveRawDatagram(uint8_t channel, uint8_t *datagram, uint8_t datagramSize)
{
    this->radio->setRFChannel(channel);

    return this->radio->receive(datagram, datagramSize, 1000);
}

bool DCServices::loop()
{
    while (Serial.available())
    {
        if (Serial.read() == '!')
        {

            this->checkForVSim();
        }
    }
}

bool DCServices::checkForVSim()
{
    char encodedVSim[64];
    unsigned long startTime = millis();
    uint8_t ix = 0;

    if (Serial.peek() == 'V')
    {
        Serial.read();

        while (true)
        {
            if (millis() - startTime > 1000)
            {
                Serial.println("vSIM ERROR");
                return;
            }

            while (Serial.available())
            {
                encodedVSim[ix++] = Serial.read();
            }

            if (Base64.decodedLength(encodedVSim, ix) == DCCORE_EEPROM_VSIM_LEN)
            {
                uint8_t decodedVSim[DCCORE_EEPROM_VSIM_LEN];
                Base64.decode(decodedVSim, encodedVSim, ix);
                eeprom_write_block(decodedVSim, DCCORE_EEPROM_VSIM_BASE, DCCORE_EEPROM_VSIM_LEN);
                Serial.println("vSIM OK");

                return;
            }
        }
    }
}
