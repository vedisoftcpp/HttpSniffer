#include "filelogger.h"

namespace logging
{

FileLogger::FileLogger(const std::string& filename) :
    _log_file(filename.c_str(), std::fstream::out)
{
}

FileLogger::~FileLogger()
{
}

void FileLogger::log(const std::string& str)
{
    _log_file << str;
    _log_file.flush();
}

}
