#include "Interface.h"
#include <vector>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

int Interface::readCommand()
{
	string input;
    Command cmd;

	getline( cin, input );
	cout << endl;
	cmd = parser->parse( input );

    

	// ENCRYPT
	if( cmd.values.size() >= 2 && cmd.name == "encrypt" )
		crypter->encryptFiles( cmd );
	// DECRYPT
	else if( cmd.values.size() >= 2 && cmd.name == "decrypt" )
		crypter->decryptFiles( cmd );
	// ANALYZE
	else if( cmd.values.size() >= 1 && cmd.name == "analyze" )
		crypter->analyzeFiles( cmd );
	// AUTO_CRYPTION
	else if( cmd.values.size() >= 2 && cmd.name == "auto" )
		crypter->autoCryption( cmd );
	// EXIT
	else if( cmd.name == "exit" )
		return 0;
	// HELP
	else if( cmd.name == "help" )
	{
		if( cmd.values.size() == 0 )
			printHelp( HELP );
		else if( cmd.values[ 0 ] == "encrypt" )
			printHelp( HELP_ENCRYPT );
		else if( cmd.values[ 0 ] == "decrypt" )
			printHelp( HELP_DECRYPT );
		else if( cmd.values[ 0 ] == "analyze" )
			printHelp( HELP_ANALYZE );
		else if( cmd.values[ 0 ] == "auto" )
			printHelp( HELP_AUTO );
		else
			printHelp( HELP );
	}
	// PUSTA LINIA
	else if( cmd.name == "" )
		return 1;
	// NIEZNANE POLECENIE 
	else
		printHelp( HELP );

	cout << endl;
	return 1; // Nie wybrano exit
}

void Interface::analyzeProgramArgs( int argc, char ** argv )
{
	Command cmd;
	cmd.name = "auto";

	string password;
	cout << "Enter password: ";
	getline( cin, password );
	cout << endl;
	cmd.values.push_back( password );

	for( int i = 0; i < argc; i++ )
	{
		cmd.values.push_back( argv[ i ] );
	}
	crypter->autoCryption( cmd );
	cout << endl;
}

Interface::Interface( CryptoEngine * _crypter, InputParser * _parser )
	:crypter( _crypter ), parser( _parser ){}

void Interface::printProgramInfo()
{
	cout << "Crypter version 1.0 (work-in-progress)" << endl << endl;
}

void Interface::printPrompt()
{
	cout << "CRYPTER> ";
}

// TODO Help
void Interface::printHelp( HelpInfo info )
{
	switch( info )
	{
	case HELP_ENCRYPT:
		cout << "ENCRYPT_HELP" << endl;
		break;
	case HELP_DECRYPT:
		cout << "DECRYPT_HELP" << endl;
		break;
	case HELP_ANALYZE:
		cout << "ANALYZE_HELP" << endl;
		break;
	case HELP_AUTO:
		cout << "AUTO_HELP" << endl;
		break;
	default:
	case HELP:
		cout << "HELP" << endl;
		break;
	}
}