#pragma once
#include "InputParser.h"

using namespace std;

vector< string > InputParser::parse( string& cmd )
{
	vector< string > parameters;
	string element = "";
	for( unsigned int i = 0; i < cmd.size(); i++ )
	{
		// Jeœli wyraz zaczyna siê od (") i nie jest to wyraz pierwszy,
		// to wczytuj do napotkania znaku ("). Znaki (") s¹ wyrzucane.
		if( cmd[ i ] == '\"' && parameters.size() > 0 )
		{
			for( i = i + 1; cmd[ i ] != '\"'; i++ )
			{
				// B³¹d parsowania. Zwraca vektor "help"
				if( i >= cmd.size() )
				{
					vector< string > vec;
					return vec;
				}
				element += cmd[ i ];
			}
			parameters.push_back( element );
			element = "";
		}
		else if( isspace( cmd[ i ] ) )
		{
			if( element == "" )
				continue;
			else
			{
				parameters.push_back( element );
				element = "";
			}
		}
		else
		{
			element += cmd[ i ];
		}
	} // for
	if( element != "" )
		parameters.push_back( element );
	if( parameters.size() == 0 )
		return vector< string >( 1, "" );

	return parameters;
}