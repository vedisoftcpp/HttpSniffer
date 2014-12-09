#ifndef CONNECTED_CLIENT_DATA_T_H
#define CONNECTED_CLIENT_DATA_T_H

#include "headers.h"

namespace HttpSniffer
{

struct connected_client_data_t
{
    int client_id;
    Socket client_socket;
    HttpStatistics* http_statistics;
    RemoveThreadFunc* remove_thread_func;
};

}

#endif // CONNECTED_CLIENT_DATA_T_H
