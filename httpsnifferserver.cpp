#include "httpsnifferserver.h"

namespace HttpSniffer
{

HttpSnifferServer::HttpSnifferServer() :
    _http_statistics(),
    _http_sniffer_thread((void*)&_http_statistics),
    _client_broker_thread((void*)&_http_statistics)
{
}

void HttpSnifferServer::run()
{
    Socket::initialize();

    _http_sniffer_thread.start();
    _client_broker_thread.start();

    while (true)
    {
        //
    }

    Socket::clean_up();
}


}
