#include "httpheaderparser.h"
#include <iostream>

namespace HttpSniffer
{

HttpHeaderParser::HttpHeaderParser()
{
}

void HttpHeaderParser::parse(std::string& header)
{
    for (size_t pos = header.find("Host: ");
         pos != std::string::npos;
         pos = header.find("Host: ", pos+6))
    {
        size_t eol = header.find("\r\n", pos);
        if (eol == std::string::npos)
            return;
        std::string url(header.begin()+pos+6, header.begin()+eol);
        std::cout << url << "\n";
        header.erase(header.begin(), header.begin()+eol);
    }
}

}
