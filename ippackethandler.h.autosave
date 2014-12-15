#ifndef IPPACKETHANDLER_H
#define IPPACKETHANDLER_H

#include "headers.h"
#include "ippacket.h"

namespace HttpSniffer
{

class IpPacketHandler
{
public:
    IpPacketHandler();

    IpPacket defragment_packet(const IpPacket& ip_packet);

private:
    typedef u_int16_t ip_packet_id;
    std::map<id_packet_id, std::vector<IpPacket> > _fragmented_packets;
};

}

#endif // IPPACKETHANDLER_H
