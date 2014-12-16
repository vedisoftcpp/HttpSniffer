#ifndef TCPDATAGRAMID_H
#define TCPDATAGRAMID_H

#include "headers.h"

namespace HttpSniffer
{

class TcpDatagramId
{
public:
    TcpDatagramId(TcpDatagram* tcp_datagram);
    TcpDatagramId(u_int32_t src_addr, u_int32_t dst_addr,
                  u_int16_t src_port, u_int16_t dst_port);

    bool operator< (const TcpDatagramId& tcp_dataram_id) const;

    TcpDatagramId get_invers_id() const;

private:
    u_int32_t _src_addr;
    u_int32_t _dst_addr;
    u_int16_t _src_port;
    u_int16_t _dst_port;
};

}

#endif // TCPDATAGRAMID_H
