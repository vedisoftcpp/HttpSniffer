#ifndef HTTPSTATISTICS_H
#define HTTPSTATISTICS_H

#include "headers.h"
#include <sstream>

#include <iostream>

namespace HttpSniffer
{

class HttpStatistics
{
public:
    HttpStatistics();
    ~HttpStatistics();
    void get(std::stringstream& stream);

    template <typename T>
    HttpStatistics& operator<<(const T & data)
    {
        //std::cout << "in mutex1\n";

        _mutex.acquire();
        _stata_stream << data;
        _mutex.release();

        //std::cout << "in mutex2\n";

        return *this;
    }

private:
    Mutex _mutex;
    std::stringstream _stata_stream;

    HttpStatistics(const HttpStatistics&);
};

}

#endif // HTTPSTATISTICS_H
