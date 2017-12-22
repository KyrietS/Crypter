#pragma once
#include "File.h"
#include <vector>
#include <string>

// TODO Klasa Help wy�wietlaj�ca wszystkie pomoce

class CryptoEngine
{
	std::vector< File > files;
	std::vector< char > key;
public:
	void encryptFiles( std::string& password, std::vector< std::string >& paths );
	void decryptFiles( std::string& password, std::vector< std::string >& paths );
	void analyzeFiles( std::vector< std::string >& paths );
	// Sprawdza czy plik jest ju� zaszyfrowany. Je�li tak, to go zaszyfruje.
	// Je�li nie, to go spr�buje odszyfrowa�.
	void autoCryption( std::string& password, std::vector< std::string >& paths );
};