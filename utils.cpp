#include "utils.h"
#include "ippacket.h"
#include "tcpdatagram.h"
#include "types.h"

#include <iostream>

namespace HttpSniffer
{

bool is_ip_packet_fragmented(const IpPacket& ip_packet)
{
    if (ip_packet.header.dont_fragment)
    {
        //std::cout << "ip_packet.header.dont_fragment\n";
        return false;
    }

    if (!ip_packet.header.more_fragments && (ip_packet.header.fragment_offset == 0))
    {
        //std::cout << "ip_packet.header.more_fragments\n";
        return false;
    }

    return true;
}

bool is_tcp_protocol(const IpPacket& ip_packet)
{
    if (ip_packet.header.protocol == 0x06)
        return true;
    else
        return false;
}

//TcpDatagram tcp_datagram_from_ip_packet(const IpPacket& ip_packet)
//{
//    TcpDatagram tcp_datagram;

//    return TcpDatagram();
//}

IpPacket create_ip_packet_from_raw(ip_header_t* ip_header)
{
    IpPacket ip_packet;
    ip_packet.header.version = ip_header->ver_ihl >> 4;
    ip_packet.header.ihl = ip_header->ver_ihl & 0x0f;
    ip_packet.header.dscp = ip_header->tos >> 2;
    ip_packet.header.ecn = ip_header->tos & 0x03;
    ip_packet.header.total_length = ntohs(ip_header->tlen);
    ip_packet.header.id = ntohs(ip_header->identification);
    ip_packet.header.dont_fragment = ((ntohs(ip_header->flags_fo) >> 13) & 0x02) != 0;
    ip_packet.header.more_fragments = ((ntohs(ip_header->flags_fo) >> 13) & 0x01) != 0;
    ip_packet.header.fragment_offset = ntohs(ip_header->flags_fo) & 0x1fff;
    ip_packet.header.ttl = ip_header->ttl;
    ip_packet.header.protocol = ip_header->proto;
    ip_packet.header.crc = ip_header->crc;
    ip_packet.header.src_addr = ntohl(*((u_int32_t*)(&ip_header->saddr)));
    ip_packet.header.dst_addr = ntohl(*((u_int32_t*)(&ip_header->daddr)));
    for (u_int i = 20; i < ip_packet.header.size(); ++i)
    {
        ip_packet.header.options.push_back( *((u_int8_t*)ip_header + i) );
    }
    for (u_int i = ip_packet.header.size(); i < ip_packet.header.total_length; ++i)
    {
        ip_packet.data.push_back( *((u_int8_t*)ip_header + i) );
    }
    return ip_packet;
}

}
