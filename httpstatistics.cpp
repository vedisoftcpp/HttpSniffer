#include "httpstatistics.h"

namespace HttpSniffer
{

HttpStatistics::HttpStatistics()
{
    _mutex.create();
}

HttpStatistics::~HttpStatistics()
{
    _mutex.close();
}

void HttpStatistics::get(std::stringstream& stream)
{
    _mutex.acquire();
    stream << _stata_stream.rdbuf();
    _mutex.release();
}

void HttpStatistics::update(const HttpStataEntry& entry)
{
    _mutex.acquire();
    std::map<std::string, HttpStataEntry>::iterator it = _statistics.find(entry.url);
    if (it == _statistics.end())
    {
        _statistics[entry.url] = entry;
    }
    else
    {
        _statistics[entry.url].timestamp = entry.timestamp;
        _statistics[entry.url].count++;
    }
    _mutex.release();
}

}
