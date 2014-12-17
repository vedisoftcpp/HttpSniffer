#include "loggermanager.h"
#include "logger.h"

namespace logging
{

LoggerManager::LoggerManager()
{
}

LoggerManager::~LoggerManager()
{
    for (std::vector<Logger*>::iterator it = _loggers.begin(); it != _loggers.end(); ++it)
    {
        delete *it;
    }
    _loggers.clear();
}

void LoggerManager::add_logger(Logger* logger)
{
    _loggers.push_back(logger);
}

void LoggerManager::log(const std::string& str)
{
    for (std::vector<Logger*>::iterator it = _loggers.begin(); it != _loggers.end(); ++it)
    {
        Logger& logger = **it;
        logger.threadsafe_log(str);
    }
}

}
