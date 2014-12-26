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

time_t HttpStatistics::get(std::stringstream& stream, int user_id, time_t start_time)
{
    time_t now = ::time(0);
    _mutex.acquire();
    if (_statistics.empty())
    {
        _mutex.release();
        return now;
    }
    else
    {
        std::vector<HttpStataEntry> entries;
        for (std::deque<HttpStataEntry>::iterator it = _statistics.begin();
             it != _statistics.end(); ++it)
        {
            HttpStataEntry& entry = *it;
            if (start_time <= entry.timestamp)
                entries.push_back(entry);
        }

        if (entries.empty())
        {
            _mutex.release();
            return now;
        }

        _client_start[user_id] = now;

        stream << "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
        std::map<std::string, HttpStataEntry> stata = get_aggregate(entries);

        for (std::map<std::string, HttpStataEntry>::iterator it = stata.begin();
             it != stata.end(); ++it)
        {
            HttpStataEntry& entry = it->second;
            stream << entry.to_str();
        }
    }
    _mutex.release();
    return now;
}

void HttpStatistics::update(const std::string& url)
{
    time_t now = time(0);
    _mutex.acquire();
//    std::map<time_t, HttpStataEntry>::iterator it = _statistics.find(url);
//    if (it == _statistics.end())
//    {
//        HttpStataEntry entry;
//        entry.url = url;
//        entry.timestamp = now;
//        entry.count = 1;
//        _statistics[url] = entry;
//    }
//    else
//    {
//        _statistics[url].timestamp = now;
//        _statistics[url].count++;
//    }

    if (_client_start.size() == 0)
    {
        _mutex.release();
        return;
    }

    HttpStataEntry entry;
    entry.url = url;
    entry.timestamp = now;
    entry.count = 1;
    _statistics.push_back(entry);

    _mutex.release();
}

}
