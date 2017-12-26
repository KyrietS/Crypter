#pragma once
#include <vector>
#include <string>
#include "Command.h"

// TODO rozwijanie regex
class InputParser
{
public:
	// Funkcja parsuje polecenie. Jeœli sk³adnia jest niepoprawna, to
    // zwraca Command::name = "help". Jeœli input by³ pustym wierszem, to
    // zwraca Command::name = "".
	 Command parse( std::string& command );
private:
    std::vector< std::string > split( std::string & command );
};