#include "tcpdatagramid.h"
#include "tcpdatagram.h"
#include "ippacket.h"

namespace HttpSniffer
{

TcpDatagramId::TcpDatagramId(TcpDatagram* tcp_datagram) :
    _src_addr(tcp_datagram->ip_packet->header.src_addr),
    _dst_addr(tcp_datagram->ip_packet->header.dst_addr),
    _src_port(tcp_datagram->header.src_port),
    _dst_port(tcp_datagram->header.dst_port)
{

}

TcpDatagramId::TcpDatagramId(u_int32_t src_addr, u_int32_t dst_addr, u_int16_t src_port, u_int16_t dst_port) :
    _src_addr(src_addr),
    _dst_addr(dst_addr),
    _src_port(src_port),
    _dst_port(dst_port)
{

}

bool TcpDatagramId::operator<(const TcpDatagramId& tcp_dataram_id) const
{
    if (_src_addr < tcp_dataram_id._src_addr)
        return true;
    else if (_src_addr > tcp_dataram_id._src_addr)
        return false;

    if (_dst_addr < tcp_dataram_id._dst_addr)
        return true;
    else if (_dst_addr > tcp_dataram_id._dst_addr)
        return false;

    if (_src_port < tcp_dataram_id._src_port)
        return true;
    else if (_src_port > tcp_dataram_id._src_port)
        return false;

    if (_dst_port < tcp_dataram_id._dst_port)
        return true;
    else if (_dst_port > tcp_dataram_id._dst_port)
        return false;

    return false;
}

TcpDatagramId TcpDatagramId::get_invers_id() const
{
    return TcpDatagramId(_dst_addr, _src_addr, _dst_port, _src_port);
}



}
