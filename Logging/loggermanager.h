#ifndef LOGGERMANAGER_H
#define LOGGERMANAGER_H

#include "headers.h"
#include "logger.h"

namespace logging
{

class LoggerManager
{
public:
    LoggerManager();
    ~LoggerManager();

    void add_logger(Logger* logger);
    void log(const std::string& str);

private:
    std::vector<Logger*> _loggers;
};

}

#endif // LOGGERMANAGER_H
