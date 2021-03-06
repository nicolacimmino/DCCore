// DCServices.
//
//  Copyright (C) 2020 Nicola Cimmino
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//   This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see http://www.gnu.org/licenses/.
//

#ifndef __DC_SERVICESLITE_H__
#define __DC_SERVICESLITE_H__

#include <Arduino.h>
#include <uRTCLib.h>
#include "RadioDrivers/RadioDriverFactory.h"
#include "RadioDrivers/RadioDriver.h"
#include "Datagrams/DCTimeDatagram.h"

#define TIME_BROADCAST_CHANNEL 64
#define DC_SERVICES_EXTENDED_PREAMBLE 64123

struct DateTime
{
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t dayOfWeek;
    bool dst;
    bool leap;
};

class DCServicesLite
{
private:
    RadioDriver *radio;
    uRTCLib *rtc;

public:
    DCServicesLite(uint8_t radioType, uRTCLib *rtc = NULL);
    bool syncRTCToTimeBroadcast();
    bool receiveTimeBroadcast(DateTime *dateTime);
};

#endif
