#ifndef PCAPIPPACKETSNIFFER_H
#define PCAPIPPACKETSNIFFER_H

#include "headers.h"
#include "ippacketsnifferbase.h"

namespace HttpSniffer
{

class PcapIpPacketSniffer : public IpPacketSnifferBase
{
public:
    PcapIpPacketSniffer();
};

}

#endif // PCAPIPPACKETSNIFFER_H
