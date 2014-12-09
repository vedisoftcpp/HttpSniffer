#ifndef HEADERS_H
#define HEADERS_H

#ifdef __unix__
//    #include "posix/thread.hpp"
//    #include "posix/mutex.h"
//    #include "posix/socket.h"
#elif defined(_WIN32) || defined(WIN32)
    #include <WinSock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    #include "win32/thread.hpp"
    #include "win32/mutex.h"
    #include "win32/socket.h"
#endif

namespace HttpSniffer
{

class Application;
class HttpSnifferServer;
class HttpSnifferProc;
class ClientBrokerProc;
class ConnectedClientProc;
class RemoveThreadFunc;
class HttpStatistics;

struct connected_client_data_t;

}

#endif // HEADERS_H
