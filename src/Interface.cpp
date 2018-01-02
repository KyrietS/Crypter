#include "Interface.h"
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
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
	const int MARGIN = 12;
	cout << left;
	switch( info )
	{
	case HELP_ENCRYPT:
		cout << "Encrypts files with a specified password." << endl << endl;
		cout << "ENCRYPT password files" << endl << endl;
		cout << setw( MARGIN ) << "  password";
		cout << " - Password to encrypt files with." << endl;
		cout << setw( MARGIN ) << "  files";
		cout << " - Specifies a list of files or directories to be encrypted." << endl;
		cout << string( MARGIN + 3, ' ' );
		cout << "If a directory is specified, all files within the directory are encrypted." << endl;
		break;
	case HELP_DECRYPT:
		cout << "Decrypts files with a specified password." << endl << endl;
		cout << "DECRYPT password files" << endl << endl;
		cout << setw( MARGIN ) << "  password";
		cout << " - Password to decrypt files with." << endl;
		cout << setw( MARGIN ) << "  files";
		cout << " - Specifies a list of files or directories to be decrypted." << endl;
		cout << string( MARGIN + 3, ' ' );
		cout << "If a directory is specified, all files within the directory are decrypted." << endl;
		break;
	case HELP_ANALYZE:
		cout << "Displays information about given files. Checks if file is encrypted." << endl << endl;
		cout << "ANALYZE files" << endl << endl;
		cout << setw( MARGIN ) << "  files";
		cout << " - Specifies a list of files or directories to be analyzed." << endl;
		cout << string( MARGIN + 3, ' ' );
		cout << "If a directory is specified, all files within the directory are analyzed." << endl;
		break;
	case HELP_AUTO:
		cout << "Decrypts if file is encrypted and encrypts if file is not encrypted." << endl << endl;
		cout << "AUTO password files" << endl << endl;
		cout << setw( MARGIN ) << "  password";
		cout << " - Password to encrypt/decrypt files with." << endl;
		cout << setw( MARGIN ) << "  files";
		cout << " - Specifies a list of files or directories to be encrypted/decrypted." << endl;
		cout << string( MARGIN + 3, ' ' );
		cout << "If a directory is specified, all files within the directory are encrypted/decrypted." << endl;
		break;
	default:
	case HELP:
		cout << setw( MARGIN ) << "ANALYZE";
		cout << " - Displays information about given files. Checks if file is encrypted." << endl;
		cout << setw( MARGIN ) << "AUTO";
		cout << " - Decrypts if file is encrypted and encrypts if file is not encrypted." << endl;
		cout << setw( MARGIN ) << "DECRYPT";
		cout << " - Decrpts files with a specified password." << endl;
		cout << setw( MARGIN ) << "ENCRYPT";
		cout << " - Encrypts files with a specified password." << endl;
		cout << setw( MARGIN ) << "EXIT";
		cout << " - Exit Crypter." << endl;
		cout << setw( MARGIN ) << "HELP";
		cout << " - Displays help for specified command" << endl;
		break;
	}
}