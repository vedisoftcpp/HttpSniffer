#ifndef HTTPSNIFFERPROC_H
#define HTTPSNIFFERPROC_H

#include "headers.h"
#include "urllogger.h"

namespace HttpSniffer
{

class HttpSnifferProc
{
public:
    HttpSnifferProc(void* data);
    ~HttpSnifferProc();

    void operator() ();

private:
    HttpStatistics* _http_statistics;
    UrlLogger _lm;
};

}

#endif // HTTPSNIFFERPROC_H
