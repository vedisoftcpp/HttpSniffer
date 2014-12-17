#include "xmllogger.h"
#include "Logging/displaylogger.h"
#include "Logging/filelogger.h"
#include "xmlentry.h"

namespace HttpSniffer
{

XmlLogger::XmlLogger(const std::string& filename)
{
    _lm.add_logger(new logging::DisplayLogger());
    _lm.add_logger(new logging::FileLogger(filename));
    _lm.log("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n");
}

void XmlLogger::log(const XmlEntry& entry)
{
    _lm.log(entry.to_str() + "\n");
}

}
