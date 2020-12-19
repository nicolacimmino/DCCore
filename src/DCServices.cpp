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
    uint8_t datagram[DC_TIME_DATAGRAM_LEN];

    this->radio->setRFChannel(TIME_BROADCAST_CHANNEL);

    if (this->radio->receive(datagram, DC_TIME_DATAGRAM_LEN, 1000))
    {        
        if (!DCDatagram::verifyCRC(datagram) || !DCDatagram::isA(datagram, DC_TIME_DATAGRAM_ID))
        {
            return false;
        }

        if (this->rtc != NULL)
        {
            this->rtc->set(
                DCTimeDatagram::getSecond(datagram),
                DCTimeDatagram::getMinute(datagram),
                DCTimeDatagram::getHour(datagram),
                DCTimeDatagram::getDayOfWeek(datagram),
                DCTimeDatagram::getDay(datagram),
                DCTimeDatagram::getMonth(datagram),
                DCTimeDatagram::getYear(datagram));
        }

        return true;
    }

    return false;
}