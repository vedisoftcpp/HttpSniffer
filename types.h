#ifndef TYPES_H
#define TYPES_H

#include "headers.h"

namespace HttpSniffer
{

struct ip_address_t
{
    u_char byte1;
    u_char byte2;
    u_char byte3;
    u_char byte4;
};

struct ip_header_t
{
    u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
    u_char  tos;            // Type of service
    u_short tlen;           // Total length
    u_short identification; // Identification
    u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
    u_char  ttl;            // Time to live
    u_char  proto;          // Protocol
    u_short crc;            // Header checksum
    ip_address_t  saddr;    // Source address
    ip_address_t  daddr;    // Destination address
    u_int   op_pad;         // Option + Padding
};

struct tcp_header_t
{
    u_short src_port;
    u_short dst_port;
    u_int seq_number;
    u_int ask_number;
    u_char stuff;
    u_char flags;
    u_short window;
    u_short checksum;
    u_short urg_ptr;
};

}

#endif // TYPES_H
