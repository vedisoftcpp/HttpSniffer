#ifndef TCPDATAGRAM_H
#define TCPDATAGRAM_H

#include "headers.h"
#include "tcpdatagramheader.h"
#include "tcpdatagramid.h"

namespace HttpSniffer
{

class TcpDatagram
{
public:
    TcpDatagram(IpPacket& _ip_packet);

    TcpDatagramHeader header;
    std::vector<u_int8_t> data;
    IpPacket* ip_packet;
    TcpDatagramId id;
};

}

#endif // TCPDATAGRAM_H
