#ifndef LOGGER_H
#define LOGGER_H

#include "headers.h"

#ifdef __unix__
    #include "../posix/mutex.h"
#elif defined(_WIN32) || defined(WIN32)
    #include "../win32/mutex.h"
#endif

namespace logging
{

class Logger
{
public:
    Logger();
    virtual ~Logger();

    virtual void log(const std::string& str) = 0;
    void threadsafe_log(const std::string& str);

private:
    Mutex _mutex;
};

}

#endif // LOGGER_H
