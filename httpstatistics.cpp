#include "httpstatistics.h"

namespace HttpSniffer
{

HttpStatistics::HttpStatistics() :
    _client_start()
{
    _mutex.create();
}

HttpStatistics::~HttpStatistics()
{
    _mutex.close();
}

void HttpStatistics::get(std::stringstream& stream, int user_id)
{
    _mutex.acquire();

    if (_statistics.empty())
    {
        _client_start[user_id] = ::time(0);
        _mutex.release();
        return;
    }
    else
    {
        time_t start_time = _client_start[user_id];

        //std::cout << "1\n";

        std::vector<HttpStataEntry> entries;
        for (std::deque<HttpStataEntry>::iterator it = _statistics.begin();
             it != _statistics.end(); ++it)
        {
            HttpStataEntry& entry = *it;
            if (start_time <= entry.timestamp)
                entries.push_back(entry);
        }

        //std::cout << "2\n";

        _client_start[user_id] = ::time(0);

        if (entries.empty())
        {
            _mutex.release();
            return;
        }

        unsafe_clean_up();

        //std::cout << "3\n";

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
}

void HttpStatistics::update(const std::string& url)
{
    _mutex.acquire();

    HttpStataEntry entry;
    entry.url = url;
    entry.timestamp = ::time(0);
    entry.count = 1;
    _statistics.push_back(entry);

    _mutex.release();
}

}
