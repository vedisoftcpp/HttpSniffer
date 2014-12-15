#ifndef IPPACKET_H
#define IPPACKET_H

#include "headers.h"

namespace HttpSniffer
{

class IpPacket
{
public:
    u_int8_t version;
    u_int8_t ihl;
    u_int8_t dscp;
    u_int8_t ecn;
    u_int16_t total_length;
    u_int16_t id;
    bool dont_fragment;
    bool more_fragments;
    u_int16_t fragment_offset;
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t crc;
    u_int32_t src_addr;
    u_int32_t dst_addr;
    std::vector<u_int8_t> options;
    std::vector<u_int8_t> data;

    u_int16_t header_size() { return ihl * 4; }
};

}

#endif // IPPACKET_H
