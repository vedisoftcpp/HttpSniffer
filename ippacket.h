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
};

}

#endif // IPPACKET_H
