#pragma once
#include <vector>
#include <string>

// TODO rozwijanie regex
class InputParser
{
public:
	// Funkcja rozbija polecenie na pojedyncze elementy.
	// Je�li sk�adnia jest niepoprawna, to zwraca pusty wektor
	// Je�li wprowadzono same znaki bia�e, to zwraca wektor pustym elementem.
	std::vector< std::string > parse( std::string& command );
};