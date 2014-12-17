#include "displaylogger.h"
#include <iostream>

namespace logging
{

DisplayLogger::DisplayLogger()
{
}

DisplayLogger::~DisplayLogger()
{

}

void DisplayLogger::log(const std::string& str)
{
    std::cout << str;
}

}
