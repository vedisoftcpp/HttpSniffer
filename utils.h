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

IpPacket create_ip_packet_from_raw(void* ip_packet_ptr);

}

#endif // UTILS_H
