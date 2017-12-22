#pragma once
#include "File.h"
#include <vector>

class CryptoEngine
{
	std::vector< File > files;
	std::vector< char > key;
public:
	void encryptFiles( std::string password, std::vector< std::string > paths );
	void decryptFiles( std::string password, std::vector< std::string > paths );
	void analyzeFiles( std::vector< std::string > paths );
};