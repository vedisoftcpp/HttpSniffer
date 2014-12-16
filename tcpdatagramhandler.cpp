#include "tcpdatagramhandler.h"
#include <iostream>

namespace HttpSniffer
{

TcpDatagramHandler::TcpDatagramHandler()
{
}

void TcpDatagramHandler::process(const TcpDatagram& tcp_datagram)
{
    std::map<TcpDatagramId, std::string>::iterator it = stream_data.find(tcp_datagram.id);
    std::map<TcpDatagramId, std::string>::iterator iit = stream_data.find(tcp_datagram.id.get_invers_id());
    if (tcp_datagram.header.fin_flag)
    {
        if (it != stream_data.end())
        {
            stream_data[tcp_datagram.id] += std::string(tcp_datagram.data.begin(), tcp_datagram.data.end());
            buffer.push_back(stream_data[tcp_datagram.id]);
            stream_data.erase(tcp_datagram.id);
        }
        else
        {
            buffer.push_back(std::string(tcp_datagram.data.begin(), tcp_datagram.data.end()));
        }

        if (iit != stream_data.end())
        {
            buffer.push_back(stream_data[tcp_datagram.id.get_invers_id()]);
            stream_data.erase(tcp_datagram.id.get_invers_id());
        }

        return;
    }

    if (tcp_datagram.header.syn_flag)
    {
        if (it != stream_data.end())
        {
            buffer.push_back(stream_data[tcp_datagram.id]);
            stream_data[tcp_datagram.id] = std::string(tcp_datagram.data.begin(), tcp_datagram.data.end());
        }
        else
        {
            stream_data[tcp_datagram.id] = std::string(tcp_datagram.data.begin(), tcp_datagram.data.end());
        }

        if (iit != stream_data.end())
        {
            buffer.push_back(stream_data[tcp_datagram.id.get_invers_id()]);
            stream_data.erase(tcp_datagram.id.get_invers_id());
        }

        return;
    }

    stream_data[tcp_datagram.id] += std::string(tcp_datagram.data.begin(), tcp_datagram.data.end());
}

}
