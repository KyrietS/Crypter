#pragma once
#include <string>
#include <vector>

struct Command
{
    std::string name;
    std::vector< std::string > values;
    std::vector< std::string > parameters;
};