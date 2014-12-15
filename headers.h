#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

#ifdef __unix__

    #include "posix/thread.hpp"
    #include "posix/mutex.h"
    #include "posix/socket.h"

#elif defined(_WIN32) || defined(WIN32)

    #include <WinSock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    #define HAVE_REMOTE 1
    #include <pcap.h>
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
class IpPacket;

struct connected_client_data_t;
struct HttpStataEntry;

}

#endif // HEADERS_H
