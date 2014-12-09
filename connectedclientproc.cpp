#include "connectedclientproc.h"
#include "removethreadfunc.h"
#include "connected_client_data_t.h"

#include <iostream>

namespace HttpSniffer
{

ConnectedClientProc::ConnectedClientProc(void* data) :
    _remove_thread_func(static_cast<connected_client_data_t*>(data)->remove_thread_func),
    _http_statistics(static_cast<connected_client_data_t*>(data)->http_statistics),
    _id(static_cast<connected_client_data_t*>(data)->client_id)
{
    std::cout << "client construcor\n" << std::endl;
}

ConnectedClientProc::~ConnectedClientProc()
{
    std::cout << "client destrucor\n" << std::endl;
    _remove_thread_func->exec(_id);
}

void ConnectedClientProc::operator()()
{
    std::cout << "thread: " << _id << std::endl;
}

}
