#ifndef XMLLOGGER_H
#define XMLLOGGER_H

#include "headers.h"
#include "Logging/loggermanager.h"

namespace HttpSniffer
{

class XmlLogger
{
public:
    XmlLogger(const std::string& filename);

    void log(const XmlEntry& entry);

private:
    logging::LoggerManager _lm;
};

}

#endif // XMLLOGGER_H
