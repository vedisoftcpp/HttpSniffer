#ifndef TCPDATAGRAMHEADER_H
#define TCPDATAGRAMHEADER_H

#include "headers.h"

namespace HttpSniffer
{

class TcpDatagramHeader
{
public:
    u_int16_t src_port;
    u_int16_t dst_port;
    u_int32_t seq_number;
    u_int32_t ask_number;
    u_int8_t data_offset;
    bool ns_flag;
    bool cwr_flag;
    bool ece_flag;
    bool urg_flag;
    bool ack_flag;
    bool psh_flag;
    bool rst_flag;
    bool syn_flag;
    bool fin_flag;
    u_int16_t window;
    u_int16_t checksum;
    u_int16_t urg_ptr;
    std::vector<u_int8_t> options;

    u_int size() const { return data_offset*4; }
};

}

#endif // TCPDATAGRAMHEADER_H
