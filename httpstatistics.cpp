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
    //stream << _stata_stream.rdbuf();
    if (_statistics.empty())
    {
        _mutex.release();
        return;
    }
    else
    {
        stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
        for (std::map<std::string, HttpStataEntry>::iterator it = _statistics.begin();
             it != _statistics.end(); ++it)
        {
            HttpStataEntry& entry = it->second;
            stream << entry.to_str();
        }
    }
    _statistics.clear();
    _mutex.release();
}

void HttpStatistics::update(const std::string& url)
{
    time_t now = time(0);
    _mutex.acquire();
    std::map<std::string, HttpStataEntry>::iterator it = _statistics.find(url);
    if (it == _statistics.end())
    {
        HttpStataEntry entry;
        entry.url = url;
        entry.timestamp = now;
        entry.count = 1;
        _statistics[url] = entry;
    }
    else
    {
        _statistics[url].timestamp = now;
        _statistics[url].count++;
    }
    _mutex.release();
}

}
