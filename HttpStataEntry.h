#ifndef HTTPSTATAENTRY_H
#define HTTPSTATAENTRY_H

#include <string>
#include <ctime>
#include "xmlentry.h"

namespace HttpSniffer
{

class HttpStataEntry : public XmlEntry
{
public:
    std::string url;
    int count;
    time_t timestamp;

    std::string to_str() const
    {
        std::stringstream ss;
        ss << "<Event>\r\n"
           << "  <Timestamp>" << timestamp << "</Timestamp>\r\n"
           << "  <URL>" << url << "</URL>\r\n"
           << "  <Count>" << count << "</Count>\r\n"
           << "</Event>\r\n";
        return ss.str();
    }
};

}

#endif // HTTPSTATAENTRY_H
