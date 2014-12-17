#ifndef HTTPHEADERPARSER_H
#define HTTPHEADERPARSER_H

#include "headers.h"

namespace HttpSniffer
{

class HttpHeaderParser
{
public:
    HttpHeaderParser();

    void parse(std::string& header);

    std::vector<std::string> buffer;
};

}

#endif // HTTPHEADERPARSER_H
