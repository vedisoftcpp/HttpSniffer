#ifndef REMOVETHREADFUNC_H
#define REMOVETHREADFUNC_H

#include "headers.h"

namespace HttpSniffer
{

class RemoveThreadFunc
{
public:
    RemoveThreadFunc(ClientBrokerProc* client_broker_proc);

    void operator() (int id);
    void exec(int id);

private:
    ClientBrokerProc* _client_broker_proc;
};

}

#endif // REMOVETHREADFUNC_H
