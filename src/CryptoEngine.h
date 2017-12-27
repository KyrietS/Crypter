#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include "Command.h"

// TODO Klasa Help wyœwietlaj¹ca wszystkie pomoce

class CryptoEngine
{
public:
	void encryptFiles( Command & command );
	void decryptFiles( Command & command );
	void analyzeFiles( Command & command );
	// Sprawdza czy plik jest ju¿ zaszyfrowany. Jeœli tak, to go zaszyfruje.
	// Jeœli nie, to go spróbuje odszyfrowaæ.
	void autoCryption( Command & command );
private:
    struct Header
    {
        std::string signature;
		std::bitset< 64 > checksum;
    };
    Header readHeader( std::ifstream & file );
	void writeHeader( Header header, std::ofstream & file );
	unsigned long long calculateChecksum( std::ifstream & file );
	std::string getFileName( std::string & path );
	bool signatureVerified( std::string signature );
};