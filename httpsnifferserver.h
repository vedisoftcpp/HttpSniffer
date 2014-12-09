#ifndef HTTPSNIFFERSERVER_H
#define HTTPSNIFFERSERVER_H

#include "headers.h"
#include "httpsnifferproc.h"
#include "clientbrokerproc.h"
#include "httpstatistics.h"

namespace HttpSniffer
{

class HttpSnifferServer
{
public:
    HttpSnifferServer();

    void run();

private:
    Thread<HttpSnifferProc> _http_sniffer_thread;
    Thread<ClientBrokerProc> _client_broker_thread;
    HttpStatistics _http_statistics;
};

}

#endif // HTTPSNIFFERSERVER_H
