#pragma once
#include <vector>
#include <string>
#include "Command.h"

// TODO rozwijanie regex
class InputParser
{
public:
	// Funkcja parsuje polecenie. Je�li sk�adnia jest niepoprawna, to
    // zwraca Command::name = "help". Je�li input by� pustym wierszem, to
    // zwraca Command::name = "".
	 Command parse( std::string& command );
private:
    std::vector< std::string > split( std::string & command );
};