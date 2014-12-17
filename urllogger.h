#ifndef URLLOGGER_H
#define URLLOGGER_H

#include "headers.h"
#include "Logging/loggermanager.h"

namespace HttpSniffer
{

class UrlLogger
{
public:
    UrlLogger(const std::string& filename);

    void log(const std::string& url);

private:
    logging::LoggerManager _lm;
};

}

#endif // URLLOGGER_H
