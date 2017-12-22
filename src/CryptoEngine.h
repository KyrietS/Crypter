#pragma once
#include "File.h"
#include <vector>
#include <string>

// TODO Klasa Help wyœwietlaj¹ca wszystkie pomoce

class CryptoEngine
{
	std::vector< File > files;
	std::vector< char > key;
public:
	void encryptFiles( std::string& password, std::vector< std::string >& paths );
	void decryptFiles( std::string& password, std::vector< std::string >& paths );
	void analyzeFiles( std::vector< std::string >& paths );
	// Sprawdza czy plik jest ju¿ zaszyfrowany. Jeœli tak, to go zaszyfruje.
	// Jeœli nie, to go spróbuje odszyfrowaæ.
	void autoCryption( std::string& password, std::vector< std::string >& paths );
};