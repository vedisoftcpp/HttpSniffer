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



}
