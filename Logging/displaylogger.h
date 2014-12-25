#ifndef DISPLAYLOGGER_H
#define DISPLAYLOGGER_H

#include "headers.h"
#include "logger.h"

namespace logging
{

class DisplayLogger : public Logger
{
public:
    DisplayLogger();
    ~DisplayLogger();

    void log(const std::string& str);
};

}

#endif // DISPLAYLOGGER_H
