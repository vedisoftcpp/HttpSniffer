#ifndef IPPACKET_H
#define IPPACKET_H

#include "headers.h"
#include "ippacketheader.h"

namespace HttpSniffer
{

class IpPacket
{
public:
    IpPacketHeader header;
    std::vector<u_int8_t> data;

    u_int16_t header_size() const { return header.ihl * 4; }
};

}

#endif // IPPACKET_H
