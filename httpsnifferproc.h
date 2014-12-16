#ifndef HTTPSNIFFERPROC_H
#define HTTPSNIFFERPROC_H

#include "headers.h"
#include "ippackethandler.h"
#include "tcpdatagramhandler.h"
#include "httpheaderparser.h"

namespace HttpSniffer
{

class HttpSnifferProc
{
public:
    HttpSnifferProc(void* data);
    ~HttpSnifferProc();

    void operator() ();

    void eject_url(const std::vector<u_char>& data);

private:
    HttpStatistics* _http_statistics;

    IpPacketSnifferBase* _ip_packet_sniffer;
    IpPacketHandler _ip_packet_handler;
    TcpDatagramHandler _tcp_datagram_handler;
    HttpHeaderParser _parser;
};

}

#endif // HTTPSNIFFERPROC_H
