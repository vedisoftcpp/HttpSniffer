#pragma once

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

#ifdef __unix__

    #include "unix/thread.hpp"
    #include "unix/mutex.h"
    #include "unix/socket.h"

#elif defined(_WIN32) || defined(WIN32)

//    #include <WinSock2.h>
//    #include <ws2tcpip.h>
//    #pragma comment(lib, "Ws2_32.lib")
//    #define HAVE_REMOTE 1
//    #include <pcap.h>
//    #include "win32/thread.hpp"
//    #include "win32/mutex.h"
//    #include "win32/socket.h"

#endif

namespace HttpSniffer
{

using std::string;

class Application;
class HttpSnifferServer;
class HttpSnifferProc;
class ClientBrokerProc;
class ConnectedClientProc;
class RemoveThreadFunc;
class HttpStatistics;

struct connected_client_data_t;
class HttpStataEntry;

}


