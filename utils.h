#ifndef UTILS_H
#define UTILS_H

#include "headers.h"
#include <string>
#include <sstream>
#include "ippacket.h"

template <typename T>
std::string t_to_string(T i)
{
    std::stringstream ss;
    std::string s;
    ss << i;
    s = ss.str();
    return s;
}

namespace HttpSniffer
{

IpPacket create_ip_packet_from_raw(ip_header_t* ip_header);

bool is_ip_packet_fragmented(const IpPacket& ip_packet);

bool is_tcp_protocol(const IpPacket& ip_packet);

struct fragmented_ordering
{
    bool operator() (const IpPacket& p1, const IpPacket& p2) const
    {
        return p1.header.fragment_offset < p2.header.fragment_offset;
    }
};

}

#endif // UTILS_H
