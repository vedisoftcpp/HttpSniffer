#ifndef TCPDATAGRAMHANDLER_H
#define TCPDATAGRAMHANDLER_H

#include "headers.h"
#include "tcpdatagram.h"
#include "tcpdatagramid.h"

namespace HttpSniffer
{

class TcpDatagramHandler
{
public:
    TcpDatagramHandler();

    void process(const TcpDatagram& tcp_datagram);

public:
    std::vector<std::string> buffer;
    std::map<TcpDatagramId, std::string> stream_data;
};

}

#endif // TCPDATAGRAMHANDLER_H
