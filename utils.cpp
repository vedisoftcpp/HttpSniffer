#include "utils.h"


namespace HttpSniffer
{

bool is_ip_packet_fragmented(const IpPacket &ip_packet)
{
    if (ip_packet.dont_fragment)
        return false;

    if (!ip_packet.more_fragments && !ip_packet.fragment_offset)
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

TcpDatagram tcp_datagram_from_ip_packet(const IpPacket &ip_packet)
{

}



}
