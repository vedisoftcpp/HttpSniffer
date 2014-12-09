#include "httpsnifferproc.h"
#include "httpstatistics.h"

#include <iostream>

namespace HttpSniffer
{

HttpSnifferProc::HttpSnifferProc(void* data) :
    _http_statistics((HttpStatistics*)data)
{
}


void HttpSnifferProc::operator()()
{
    int i = 0;
    while (true)
    {
        ::Sleep(1000);
        i++;

        //std::cout << "\nSNIFFER PROC:" << i << "\n";

        (*_http_statistics) << i;

        //std::cout << "\nSNIFFER PROC2:" << i << "\n";
    }
}

}
