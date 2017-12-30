#pragma once
#include "CryptoEngine.h"
#include "InputParser.h"

class Interface
{
	CryptoEngine * crypter;
	InputParser * parser;
	std::vector< std::string > args;
public:
	Interface( CryptoEngine * _crypter, InputParser * _parser );
	int readCommand();
	void analyzeProgramArgs( int argc, char ** argv );
	void printProgramInfo();
	void printPrompt();
	void newLine();

private:
	enum HelpInfo { HELP, HELP_ENCRYPT, HELP_DECRYPT, HELP_ANALYZE, HELP_AUTO };
	void printHelp( HelpInfo info );
};