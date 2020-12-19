#include <Arduino.h>
#include "NRF24L01RadioDriver.h"
#include "uRTCLib.h"

#define TIME_BROADCAST_CHANNEL 32

extern NRF24L01RadioDriver *radio;

extern void broadcastTime();

extern uRTCLib *rtc;