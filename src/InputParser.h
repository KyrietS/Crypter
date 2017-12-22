#pragma once
#include <vector>
#include <string>

// TODO rozwijanie regex
class InputParser
{
public:
	// Funkcja rozbija polecenie na pojedyncze elementy.
	// Jeœli sk³adnia jest niepoprawna, to zwraca pusty wektor
	// Jeœli wprowadzono same znaki bia³e, to zwraca wektor pustym elementem.
	std::vector< std::string > parse( std::string& command );
};