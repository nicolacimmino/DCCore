# DCCore

Data Cloud Core is the repo for all the common code of the connected devices at my desk. These basic building blocks are used in several other projects to disseminate time, environmental information and other data wirelessly.

# Datagrams

## Datagram Header

Every datagram has a header. The header format does not change with the datagram type.

![Stack](docs/DatagramHeader.png)

**DID7..0** Datagram ID. An 8-bit ID of the datagram type. Below a list of datagram types.

|ID|Type|
|--|---|
|0x20|Time|

**DLEN7..0** Datagram Length. Length in bytes of the datagram, including the whole header and payload.

**HMAC31..0** Datagram signature. A signature calculated on the datagram payload, prefixed by all the header octets except the HMAC itself, and a secret key. The secret key is an 8-octet key shared among all devices and never transmitted across the netwrok. The HMAC (keyed-hash message authentication code) is a HMAC-SHA256 truncated to 4 octets.

## Time Datagram (0x20)

A time datagram carries information about current local date and time. While the broadcast time is taken from an accurate source (NTP or Radio signals such as DCF-77), this broadcast -due the the varied nature of the radio schemes, hardware, and software in the radio stack- is not meant to provide "atomic clock" precision time, the time will however be correct with 1 second accuracy or better.

![Stack](docs/TimeDatagram.png)

**Octets 0..5** See "Datagram Header" above.

**LEAP** If set the current year is a leap year.

**YEAR6..0** Year last two digits (00-99) of the current year.

**MONTH3..0** Current month (1-12)

**DOW2..0** Current day of the week (0=MON, 7=SUN)

**DOW4..0** Current day (1-31)

**DST** If set the Daylight Savings Time (summer time) is active.

**HOUR4..0** Current hour in 24-hour format (0-23)

**HOUR5..0** Current minute (0-59)

**HOUR5..0** Current second (0-59)





