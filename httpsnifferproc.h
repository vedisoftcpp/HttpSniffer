#ifndef HTTPSNIFFERPROC_H
#define HTTPSNIFFERPROC_H

#include "headers.h"

namespace HttpSniffer
{

class HttpSnifferProc
{
public:
    HttpSnifferProc(void* data);

    void operator() ();

    void eject_url(const std::vector<u_char>& data);

private:
    HttpStatistics* _http_statistics;
};

}

#endif // HTTPSNIFFERPROC_H
