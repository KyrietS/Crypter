#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <bitset>
#include "Command.h"

// TODO Klasa Help wy�wietlaj�ca wszystkie pomoce

class CryptoEngine
{
public:
	void encryptFiles( Command & command );
	void decryptFiles( Command & command );
	void analyzeFiles( Command & command );
	// Sprawdza czy plik jest ju� zaszyfrowany. Je�li tak, to go zaszyfruje.
	// Je�li nie, to go spr�buje odszyfrowa�.
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