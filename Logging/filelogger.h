#ifndef FILELOGGER_H
#define FILELOGGER_H

#include "headers.h"
#include "logger.h"
#include <fstream>

namespace logging
{

class FileLogger : public Logger
{
public:
    FileLogger(const std::string& filename);
    ~FileLogger();

    void log(const std::string &str);

private:
    std::fstream _log_file;
};

}

#endif // FILELOGGER_H
