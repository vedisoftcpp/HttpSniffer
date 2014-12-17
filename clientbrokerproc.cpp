#include "clientbrokerproc.h"
#include "removethreadfunc.h"
#include "connected_client_data_t.h"
#include "httpstatistics.h"

#include <iostream>

namespace HttpSniffer
{

ClientBrokerProc::ClientBrokerProc(void* data) :
    _http_statistics((HttpStatistics*)data)
{
    _client_threads_mutex.create();
}

ClientBrokerProc::~ClientBrokerProc()
{
    _client_threads_mutex.close();
}

void ClientBrokerProc::operator()()
{
    Socket server_socket;
    server_socket.bind(27015);
    server_socket.listen();

    int client_id = 0;
    RemoveThreadFunc remove_thread_func(this);
    connected_client_data_t connected_client_data;
    connected_client_data.remove_thread_func = &remove_thread_func;
    connected_client_data.http_statistics = _http_statistics;
    while (true)
    {
        //std::cout << "create client thread: " << client_id << std::endl;

        connected_client_data.client_socket = server_socket.accept();
        connected_client_data.client_id = client_id;

        //std::cout << "accept client!!! " << std::endl;

        _client_threads_mutex.acquire();
        _client_threads[client_id] = new Thread<ConnectedClientProc>((void*)&connected_client_data);
        _client_threads[client_id]->start();
        _client_threads_mutex.release();
        client_id++;

        //std::cout << "ololo: " << client_id << std::endl;

        if (client_id >= 10)
            break;
    }
}

void ClientBrokerProc::remove_thread_by_id(int id)
{
    Thread<ConnectedClientProc>* thread_ptr;
    _client_threads_mutex.acquire();
    std::map<int, Thread<ConnectedClientProc>* >::iterator it = _client_threads.find(id);
    if (it != _client_threads.end())
    {
        thread_ptr = it->second;
        _client_threads.erase(it);
        delete thread_ptr;
    }
    _client_threads_mutex.release();
}

}

