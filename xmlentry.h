#ifndef XMLENTRY_H
#define XMLENTRY_H

#include "headers.h"

namespace HttpSniffer
{

class XmlEntry
{
public:
    virtual std::string to_str() const = 0;
};


}

#endif // XMLENTRY_H
