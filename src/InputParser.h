#pragma once
#include <vector>
#include <string>

class InputParser
{
public:
	InputParser();
	std::vector< std::string > parse( std::string& command );
};