#ifndef HTTPSTATISTICS_H
#define HTTPSTATISTICS_H

#include "headers.h"
#include <sstream>
#include <map>
#include "HttpStataEntry.h"

#include <iostream>

namespace HttpSniffer
{

class HttpStatistics
{
public:
    HttpStatistics();
    ~HttpStatistics();
    void get(std::stringstream& stream);
    void update(const std::string& url);

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

    //template<>
//    HttpStatistics& operator<<(const HttpStataEntry & entry)
//    {
//        _mutex.acquire();
//        _mutex.release();

//        return *this;
//    }

private:
    Mutex _mutex;
    std::stringstream _stata_stream;
    std::map<std::string, HttpStataEntry> _statistics;

    HttpStatistics(const HttpStatistics&);
};

}

#endif // HTTPSTATISTICS_H
