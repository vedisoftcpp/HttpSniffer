#include "pcapippacketsniffer.h"
#include "ippacket.h"

namespace HttpSniffer
{

PcapIpPacketSniffer::PcapIpPacketSniffer()
{
}

void PcapIpPacketSniffer::init()
{

}

IpPacket PcapIpPacketSniffer::get_ip_packet()
{
    return IpPacket(0,0,0,0);
}

}
