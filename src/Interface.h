#pragma once
#include "CryptoEngine.h"
#include "InputParser.h"

class Interface
{
	CryptoEngine * crypter;
	InputParser * parser;
public:
	Interface( CryptoEngine * _crypter, InputParser * _parser );
	int readCommand();
	void analyzeProgramArgs( int argc, char ** argv );
};