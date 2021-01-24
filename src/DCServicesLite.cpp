#include "DCServicesLite.h"

/**
 * Constructor.
 * 
 * Parameters:
 * radioType    Radio harware type as declared in RadioDriver.h DC_RADIO_xxxx
 */
DCServicesLite::DCServicesLite(uint8_t radioType, uRTCLib *rtc = NULL)
{
    this->radio = RadioDriverFactory::createRadio(radioType);
    radio->setRXExtendedPreamble(DC_SERVICES_EXTENDED_PREAMBLE);
    radio->setTXExtendedPreamble(DC_SERVICES_EXTENDED_PREAMBLE);
    radio->setTXPower(3);

    this->rtc = rtc;
}

bool DCServicesLite::syncRTCToTimeBroadcast()
{
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

bool DCServicesLite::receiveTimeBroadcast(DateTime *dateTime)
{
    uint8_t datagram[DC_TIME_DATAGRAM_LEN];

    this->radio->setRFChannel(TIME_BROADCAST_CHANNEL);

    if (this->radio->receive(datagram, DC_TIME_DATAGRAM_LEN, 1000))
    {        
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
