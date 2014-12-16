#include "tcpdatagram.h"
#include "ippacket.h"
#include "types.h"

namespace HttpSniffer
{

TcpDatagram::TcpDatagram(IpPacket& _ip_packet) :
    ip_packet(&_ip_packet),
    id(this)
{
    tcp_header_t* th = (tcp_header_t*)&_ip_packet.data[0];
    header.src_port = ntohs(th->src_port);
    header.dst_port = ntohs(th->dst_port);
    header.seq_number = ntohl(th->seq_number);
    header.ask_number = ntohl(th->ask_number);
    header.data_offset = th->stuff >> 4;
    header.ns_flag = (th->stuff & 0x01) != 0;
    header.cwr_flag = (th->flags & 0x80) != 0;
    header.ece_flag = (th->flags & 0x40) != 0;
    header.urg_flag = (th->flags & 0x20) != 0;
    header.ack_flag = (th->flags & 0x10) != 0;
    header.psh_flag = (th->flags & 0x8) != 0;
    header.rst_flag = (th->flags & 0x4) != 0;
    header.syn_flag = (th->flags & 0x2) != 0;
    header.fin_flag = (th->flags & 0x1) != 0;
    header.window = ntohs(th->window);
    header.checksum = ntohs(th->checksum);
    header.urg_ptr = ntohs(th->urg_ptr);
    for (u_int i = 20; i < header.size(); ++i)
    {
       header.options.push_back( *((u_int8_t*)th + i) );
    }
    for (u_int i = header.size(); i < ip_packet->data.size(); ++i)
    {
        data.push_back( *((u_int8_t*)th + i) );
    }
}




}
