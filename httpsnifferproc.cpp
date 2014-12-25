#include "httpsnifferproc.h"
#include "httpstatistics.h"
#include "HttpStataEntry.h"
#include "utils.h"

#include <http_sniffer/headers.h>
#include <http_sniffer/httpheaderdetectorfactory.h>
#include <http_sniffer/tcpstreamswitch.h>
#include <http_sniffer/pcapippacketreciever.h>

namespace HttpSniffer
{

HttpSnifferProc::HttpSnifferProc(void* data) :
    _http_statistics((HttpStatistics*)data),
    _lm("urls.log")
{
}

HttpSnifferProc::~HttpSnifferProc()
{
}

void HttpSnifferProc::operator()()
{
    vector<string> urls;
    PcapIpPacketReciever ip_packet_reciever;
    TcpStreamSwitch tcp_stream_switch;
    HttpHeaderDetectorFactory http_header_detector_factory(urls);
    tcp_stream_switch.set_tcp_stream_handler_factory(http_header_detector_factory);
    ip_packet_reciever.set_tcp_stream_switch(tcp_stream_switch);
    ip_packet_reciever.init();
    while (true)
    {
        ip_packet_reciever.work();
        if (!urls.empty())
        {
            for (vector<string>::iterator it = urls.begin(); it != urls.end(); ++it)
            {
                _lm.log(*it);
                _http_statistics->update(*it);
            }
            urls.clear();
        }
    }
}


}
