#ifndef IPPACKETSNIFFERBASE_H
#define IPPACKETSNIFFERBASE_H

#include "headers.h"
#include "ippacket.h"

namespace HttpSniffer
{

class IpPacketSnifferBase
{
public:
    IpPacketSnifferBase();

    virtual IpPacket get_ip_packet() = 0;
};

}

#endif // IPPACKETSNIFFERBASE_H
