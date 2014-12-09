#ifndef APPLICATION_H
#define APPLICATION_H

#include "headers.h"
#include "httpsnifferserver.h"


namespace HttpSniffer
{

class Application
{
public:
    Application() :
        _http_sniffer_server()
    {

    }

    void run()
    {
        _http_sniffer_server.run();
    }

private:
    HttpSnifferServer _http_sniffer_server;
};

}

#endif // APPLICATION_H
