#include "urllogger.h"
#include "Logging/displaylogger.h"
#include "Logging/filelogger.h"

namespace HttpSniffer
{

UrlLogger::UrlLogger(const std::string& filename)
{
    _lm.add_logger(new logging::DisplayLogger());
    _lm.add_logger(new logging::FileLogger(filename));
}

void UrlLogger::log(const std::string& url)
{
    _lm.log(url + "\n");
}

}
