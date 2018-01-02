#pragma once
#include "InputParser.h"
#include <cctype> // tolower

using namespace std;

Command InputParser::parse( string& cmd )
{
    vector< string > splittedCommand = split( cmd );
    Command command;
    if( splittedCommand.size() == 0 )
    {
        command.name = "help";
        return command;
    }
    if( splittedCommand[ 0 ] == "" )
        return command;

	// tolower command name
	for( char & x : splittedCommand[ 0 ] )
		x = tolower( x );

	command.name = splittedCommand[ 0 ];

    for( unsigned int i = 1; i < splittedCommand.size(); i++ )
    {
        if( splittedCommand[ i ][ 0 ] == '-' )
            command.parameters.push_back( splittedCommand[ i ] );
        else
            command.values.push_back( splittedCommand[ i ] );
    }
    return command;
}

vector< string > InputParser::split( string & cmd )
{
    vector< string > parameters;
    string element = "";
    for( unsigned int i = 0; i < cmd.size(); i++ )
    {
        // Jeœli wyraz zaczyna siê od (") i nie jest to wyraz pierwszy,
        // to wczytuj do napotkania znaku ("). Znaki (") s¹ wyrzucane.
        if( cmd[ i ] == '\"' && parameters.size() > 0 )
        {
			i = i + 1;
			do
            {
                // B³¹d parsowania. Zwraca pusty wektor.
                if( i >= cmd.size() )
                {
                    vector< string > vec;
                    return vec;
                }
                element += cmd[ i ];
				i++;
			} while( cmd[ i ] != '\"' );
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