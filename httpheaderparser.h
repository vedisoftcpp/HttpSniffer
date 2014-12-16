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
};

}

#endif // HTTPHEADERPARSER_H
