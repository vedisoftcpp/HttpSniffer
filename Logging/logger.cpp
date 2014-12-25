#include "logger.h"

namespace logging
{

Logger::Logger()
{
    _mutex.create();
}

Logger::~Logger()
{
    _mutex.close();
}

void Logger::threadsafe_log(const std::string& str)
{
    _mutex.acquire();
    log(str);
    _mutex.release();
}

}
