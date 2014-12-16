#include "utils.h"
#include "ippacket.h"
#include "tcpdatagram.h"

namespace HttpSniffer
{

bool is_ip_packet_fragmented(const IpPacket& ip_packet)
{
    if (ip_packet.header.dont_fragment)
        return false;

    if (!ip_packet.header.more_fragments && !ip_packet.header.fragment_offset)
        return false;

    return true;
}

bool is_tcp_protocol(const IpPacket& ip_packet)
{
    if (ip_packet.header.protocol == 0x06)
        return true;
    else
        return false;
}

TcpDatagram tcp_datagram_from_ip_packet(const IpPacket& ip_packet)
{
    return TcpDatagram();
}



}
