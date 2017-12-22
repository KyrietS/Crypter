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
private:
	void printHelp();
	void printHelpEncrypt();
	void printHelpDecrypt();
	void printHelpAnalyze();
	void printHelpAuto();
};