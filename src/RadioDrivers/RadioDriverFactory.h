// RadioDriverFactory
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

#ifndef __RADIO_DRIVER_FACTORY_H__
#define __RADIO_DRIVER_FACTORY_H__

#include <Arduino.h>
#include "RadioDriver.h"
#include "NRF24L01RadioDriver.h"

#define DC_RADIO_NRF24_V1 1
#define DC_RADIO_NRF24_V2 2
#define DC_RADIO_NRF24_V3 3

class RadioDriverFactory
{
private:
public:
    static RadioDriver *createRadio(uint8_t radioType);
};

#endif
