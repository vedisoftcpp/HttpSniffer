#ifndef HTTPSTATAENTRY_H
#define HTTPSTATAENTRY_H

#include <string>
#include <ctime>

namespace HttpSniffer
{

struct HttpStataEntry
{
    std::string url;
    int count;
    time_t timestamp;
};

}

#endif // HTTPSTATAENTRY_H
