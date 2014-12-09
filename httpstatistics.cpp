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

}
