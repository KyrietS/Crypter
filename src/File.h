#pragma once
#include <fstream>

class File
{
	std::fstream file;
public:
	std::string path;
	File( std::string _path );
	std::string readBytes( int bytes );
	std::string writeBytes( const char * bytes );
};