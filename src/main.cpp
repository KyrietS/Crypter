#include "Interface.h"
#include "CryptoEngine.h"
#include "InputParser.h"

using namespace std;

int main( int argc, char ** argv )
{
	CryptoEngine cryptoEngine;
	InputParser parser;
	Interface interface( &cryptoEngine, &parser );

	if( argc > 1 )
	{
		interface.analyzeProgramArgs( argc - 1, argv + 1 );
	}
	else
	{
		interface.printProgramInfo();
		do
		{
			interface.printPrompt();
		} while( interface.readCommand() );
	}

	return 0;
}