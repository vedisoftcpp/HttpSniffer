#ifndef CONNECTEDCLIENTPROC_H
#define CONNECTEDCLIENTPROC_H

#include "headers.h"

namespace HttpSniffer
{

class ConnectedClientProc
{
public:
    ConnectedClientProc(void* data);
    ~ConnectedClientProc();

    void operator() ();

    void id(int id) { _id = id; }
    int id() { return _id; }

private:
    int _id;
    RemoveThreadFunc* _remove_thread_func;
    HttpStatistics* _http_statistics;
    Socket _client_socket;
};

}

#endif // CONNECTEDCLIENTPROC_H
