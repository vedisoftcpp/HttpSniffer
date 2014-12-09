#include "removethreadfunc.h"
#include "clientbrokerproc.h"

namespace HttpSniffer
{

RemoveThreadFunc::RemoveThreadFunc(ClientBrokerProc* client_broker_proc) :
    _client_broker_proc(client_broker_proc)
{
}

void RemoveThreadFunc::operator() (int id)
{
    exec(id);
}

void RemoveThreadFunc::exec(int id)
{
    _client_broker_proc->remove_thread_by_id(id);
}

}
