#include "Interface.h"
#include "CryptoEngine.h"
#include "InputParser.h"

using namespace std;

int main( int argc, char ** argv )
{
	CryptoEngine cryptoEngine;
	InputParser parser;
	Interface interface( &cryptoEngine, &parser );

	interface.printProgramInfo();
	if( argc > 1 )
	{
		interface.analyzeProgramArgs( argc - 1, argv + 1 );
	}

	do
	{
		interface.printPrompt();
	} while( interface.readCommand() );


	return 0;
}