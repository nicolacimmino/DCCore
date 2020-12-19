#include "RadioDriverFactory.h"

RadioDriver *RadioDriverFactory::createRadio(uint8_t radioType)
{
    switch (radioType)
    {
    case DC_RADIO_NRF24_V1:
        return new NRF24L01RadioDriver(1);
    case DC_RADIO_NRF24_V2:
        return new NRF24L01RadioDriver(2);
    }

    return NULL;
}