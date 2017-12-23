#include "Interface.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int Interface::readCommand()
{
	string cmd;
	vector< string > args;

	getline( cin, cmd );
	cout << endl;
	args = parser->parse( cmd );

	// NIEPOPRAWNA SK£ADNIA POLECENIA
	if( args.size() == 0 )
		printHelp( HELP );
	// ENCRYPT
	else if( args.size() >= 3 && args[ 0 ] == "encrypt" )
		crypter->encryptFiles( args[ 1 ], vector<string>( args.cbegin()+2, args.cend() ) );
	// DECRYPT
	else if( args.size() >= 3 && args[ 0 ] == "decrypt" )
		crypter->decryptFiles( args[ 1 ], vector<string>( args.cbegin() + 2, args.cend() ) );
	// ANALYZE
	else if( args.size() >= 3 && args[ 0 ] == "analyze" )
		crypter->analyzeFiles( vector<string>( args.cbegin()+1, args.cend() ) );
	// AUTO_CRYPTION
	else if( args.size() >= 3 && args[ 0 ] == "auto" )
		crypter->autoCryption( args[ 1 ], vector<string>( args.cbegin()+1, args.cend() ) );
	// EXIT
	else if( args[ 0 ] == "exit" )
		return 0;
	// HELP
	else if( args[ 0 ] == "help" )
	{
		if( args.size() == 1 )
			printHelp( HELP );
		else if( args[ 1 ] == "encrypt" )
			printHelp( HELP_ENCRYPT );
		else if( args[ 1 ] == "decrypt" )
			printHelp( HELP_DECRYPT );
		else if( args[ 1 ] == "analyze" )
			printHelp( HELP_ANALYZE );
		else if( args[ 1 ] == "auto" )
			printHelp( HELP_AUTO );
		else
			printHelp( HELP );
	}
	// PUSTA LINIA
	else if( args.size() == 1 && args[ 0 ] == "" )
		return 1;
	// NIEZNANE POLECENIE 
	else
		printHelp( HELP );

	cout << endl;
	return 1; // Nie wybrano exit
}

void Interface::analyzeProgramArgs( int argc, char ** argv )
{
	vector< string > paths;
	string password;
	for( int i = 0; i < argc; i++ )
	{
		paths.push_back( argv[ i ] );
	}
	cout << "PASSWORD: ";
	cin >> password;
	crypter->autoCryption( password, paths );
	cout << "Press ENTER to exit...";
	cin.get();
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