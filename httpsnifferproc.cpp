#include "httpsnifferproc.h"
#include "httpstatistics.h"
#include "HttpStataEntry.h"
#include "utils.h"
#include "pcapippacketsniffer.h"

namespace HttpSniffer
{

HttpSnifferProc::HttpSnifferProc(void* data) :
    _http_statistics((HttpStatistics*)data),
    _ip_packet_sniffer(new PcapIpPacketSniffer())
{
}

HttpSnifferProc::~HttpSnifferProc()
{
    if (_ip_packet_sniffer != NULL)
        delete _ip_packet_sniffer;
}

void HttpSnifferProc::operator()()
{
    while (true)
    {
        IpPacket ip_packet = _ip_packet_sniffer->get_ip_packet();
        if (!is_tcp_protocol(ip_packet))
            continue;
        try
        {
            ip_packet = _ip_packet_handler.defragment_packet(ip_packet);
        }
        catch(...)
        {
        }

        TcpDatagram tcp_datagram = tcp_datagram_from_ip_packet(ip_packet);
        if (tcp_datagram.header.dst_port == 80)
        {
            _tcp_datagram_handler.process(tcp_datagram);
        }
        else if (tcp_datagram.header.src_port == 80)
        {
            if (tcp_datagram.header.fin_flag)
                _tcp_datagram_handler.process(tcp_datagram);
        }
        else
            continue;

        for (std::vector<std::string>::iterator it = _tcp_datagram_handler.buffer.begin();
             it != _tcp_datagram_handler.buffer.end(); ++it)
        {
            _parser.parse(*it);
        }
        _tcp_datagram_handler.buffer.clear();

        for (std::map<TcpDatagramId, std::string>::iterator it = _tcp_datagram_handler.stream_data.begin();
             it != _tcp_datagram_handler.stream_data.end(); ++it)
        {
            _parser.parse(it->second);
        }
    }
}


}
