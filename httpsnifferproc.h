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
};

}

#endif // HTTPSNIFFERPROC_H
