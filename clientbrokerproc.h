#ifndef CLIENTBROKERPROC_H
#define CLIENTBROKERPROC_H

#include "headers.h"
#include "connectedclientproc.h"
#include <map>

namespace HttpSniffer
{

class ClientBrokerProc
{
public:
    ClientBrokerProc(void* data);

    void operator() ();

    void remove_thread_by_id(int id);

private:
    std::map<int, Thread<ConnectedClientProc>* > _client_threads;
    Mutex _client_threads_mutex;
    HttpStatistics* _http_statistics;
};

}

#endif // CLIENTBROKERPROC_H
