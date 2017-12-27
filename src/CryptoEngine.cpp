#pragma once
#include "CryptoEngine.h"
#include <iostream>
#include <iomanip>

using namespace std;

void CryptoEngine::encryptFiles( Command & cmd )
{
	// Nie ma przynajmniej 2 argumentów: has³o + plik
    if( cmd.values.size() < 2 )
        return;

    ifstream source;
    ofstream dest;
    string key = cmd.values[ 0 ];
	string extension = ".encrypted";
    for( unsigned int i = 1; i < cmd.values.size(); i++ )
    {
		// ------------- OPENING FILES ------------- //
		source.clear();
		if( source.is_open() )
			source.close();
        source.open( cmd.values[ i ], ios::binary );
        if( !source.good() )
        {
            cout << "Error:\tcan't open file \"" << cmd.values[ i ] << "\"" << endl;
            continue;
        }
		dest.clear();
		if( dest.is_open() )
			dest.close();
        dest.open( cmd.values[ i ] + extension, ios::binary );
        if( !dest.good() )
        {
            cout << "Error:    can't create file \"" << cmd.values[ i ] + extension << "\"" << endl;
            continue;
        }
		// ------------- HEADER ------------- //
        Header header = readHeader( source );
        if( header.signature == string( "CRYPTER\0", 8 ) )
        {
            cout << "Warning:  the file you want to encrypt seems to be already encrypted." << endl;
        }

		header.signature = string( "CRYPTER\0", 8 );
		header.checksum = calculateChecksum( source );
		if( header.checksum == 0uLL )
		{
			cout << "Error:    can't calculate checksum in file: \"" << cmd.values[ i ] << "\"" << endl;
			continue;
		}

		writeHeader( header, dest );

		// ------------- ENCRYPTION ------------- //
		char byte = 0;
		source.seekg( 0 );
		unsigned long long j = 0;
		while( source.get( byte ) )
		{
			byte = byte ^ key[ j % key.size() ]; 	// szyfrowanie bajta
			dest.put( byte );
			j++;
		}
		// --------------------------------------- //

		source.close();
		dest.close();
		cout << "Encrypted file: " << cmd.values[ i ] + extension << endl;
    }
}

void CryptoEngine::decryptFiles( Command & cmd )
{
	// Nie ma przynajmniej 2 argumentów: has³o + plik
	if( cmd.values.size() < 2 )
		return;

	ifstream source;
	ofstream dest;
	string key = cmd.values[ 0 ];
	unsigned long long checksum = 0uLL;
	string extension = ".encrypted";
	for( unsigned int i = 1; i < cmd.values.size(); i++ )
	{
		// ------------- OPENING FILES ------------- //
		source.clear();
		if( source.is_open() )
			source.close();
		source.open( cmd.values[ i ], ios::binary );
		if( !source.good() )
		{
			cout << "Error:\tcan't open file \"" << cmd.values[ i ] << "\"" << endl;
			continue;
		}
		dest.clear();
		if( dest.is_open() )
			dest.close();
		string destPath = cmd.values[ i ];
		if( destPath.rfind( extension ) + extension.size() == destPath.size() )
			destPath = string( destPath.begin(), destPath.end() - extension.size() );
		dest.open( destPath, ios::binary );
		if( !dest.good() )
		{
			cout << "Error:    can't create file \"" << destPath << "\"" << endl;
			continue;
		}
		// ------------- HEADER ------------- //
		Header header = readHeader( source );
		if( header.signature == string( "CRYPTER\0", 8 ) && header.checksum != 0uLL )
		{
			checksum = header.checksum.to_ullong();
			source.seekg( 16, ios::beg );
		}
		else
		{
			cout << "Warning:  file does not seem to be encrypted";
			source.seekg( 0 );
		}

		// ------------- DECRYPTION ------------- //
		char byte = 0;
		unsigned long long j = 0;
		while( source.get( byte ) )
		{
			byte = byte ^ key[ j % key.size() ]; 	// szyfrowanie bajta
			dest.put( byte );
			j++;
		}
		source.close();
		dest.close();
		// ------ POPRAWNOŒÆ DESZYFRACJI ------- //
		if( checksum != 0uLL )
		{
			ifstream decryptedFile( destPath, ios::binary );
			if( decryptedFile.good() )
			{
				unsigned long long decryptedFileChecksum = calculateChecksum( decryptedFile );
				if( checksum == decryptedFileChecksum )
					cout << "Decryption correct: " << destPath << endl;
				else
				{
					cout << "Error:    decryption incorrect: " << destPath << endl;
				}
			}
			else
				cout << "Decrypred file: " << destPath << endl;
			decryptedFile.close();
		}
		else
		{
			cout << "Decrypted file: " << destPath << endl;
		}
	}
}

void CryptoEngine::analyzeFiles( Command & cmd )
{
	for( int i = 0; i < cmd.values.size(); i++ )
	{
		// Zapisz obecne flagi strumienia
		ios::fmtflags flags( cout.flags() );
		if( i > 0 )
			cout << endl;
		cout << "File \"" << cmd.values[ i ] << "\":" << endl << endl;
		ifstream file( cmd.values[ i ] );
		if( !file.good() )
		{
			cout << "  " << left << setw( 10 ) << "Error"
				<< ": can't open the file" << endl;
			continue;
		}
		cout << left;
		cout << setfill( '.' );
		cout << "  " << setw( 10 ) << "Name"
			<< ": " << getFileName( cmd.values[ i ] ) << endl;
		Header header = readHeader( file );
		if( signatureVerified( header.signature ) )
		{
			cout << "  " << setw( 10 ) << "Encrypted" << ": yes" << endl;
			cout << "  " << setw( 10 ) << "Checksum" << ": "
				<< hex << uppercase << header.checksum.to_ullong() << endl;
		}
		else
			cout << "  " << setw( 10 ) << "Encrypted" << ": no" << endl;
		

		// Przywróæ pierowtne flagi strumienia
		cout.flags( flags );
	}
}

void CryptoEngine::autoCryption( Command & cmd )
{
    string key = cmd.values[ 0 ];
    cout << "(de)szyfrowanie " << cmd.values.size() - 1 << " plikow haslem: " << cmd.values[ 0 ] << endl;
    for( unsigned int i = 1; i < cmd.values.size(); i++ )
        cout << cmd.values[ i ] << endl;
    cout << "Parametry: " << endl;
    for( auto & x : cmd.parameters )
        cout << x << endl;
}

CryptoEngine::Header CryptoEngine::readHeader( ifstream & file )
{
    Header header;
    if( !file.is_open() || !file.good() ) // Plik nie jest otwarty
    {
        header.signature = "";
        return header;
    }

    file.seekg( 0 );    // Ustaw wskaŸnik czytania na pocz¹tek pliku
    char signature[ 8 ];
    file.read( signature, 8 );  // Odczytaj 8 bajtów
    
    if( !file.good() )  // Wyst¹pi³ b³¹d, np. koniec pliku
    {
        header.signature = "";
        file.clear();
        return header;
    }

    header.signature = string( signature, 8 );

    unsigned char c_checksum[ 8 ];
    file.read( (char*)c_checksum, 8 );

    if( !file.good() )  // Wyst¹pi³ b³¹d, np. koniec pliku
    {
        header.signature = "";
        file.clear();
        return header;
    }

	// parsowanie bajtów z tablicy c_checksum na liczbê long long
    unsigned long long checksum = 0;
    for( int i = 0; i <= 6; i++ )
        checksum = (checksum | (unsigned char)c_checksum[ i ]) << 8;
    checksum = (checksum | (unsigned char)c_checksum[ 7 ]);

	// Niejawna konwersja z long long do bitset<64>
	// rozbija liczbê long long na pojedyncze bity.
	// Najmniej znacz¹cy bit to header.checksum[ 0 ].
    header.checksum = checksum;

    return header;
}

void CryptoEngine::writeHeader( Header header, ofstream & file )
{
	file.write( header.signature.c_str(), 8 );
	bitset<64> checksum( header.checksum );

	// Przepisywanie 64 bitów na tablicê 8 bajtów
	char c_checksum[ 8 ];
	for( int i = 7; i >= 0; i-- )
	{
		c_checksum[ i ] = checksum[ 56 - i * 8 ] + 2 * checksum[ 57 - i * 8 ]
			+ 4 * checksum[ 58 - i * 8 ] + 8 * checksum[ 59 - i * 8 ]
			+ 16 * checksum[ 60 - i * 8 ] + 32 * checksum[ 61 - i * 8 ]
			+ 64 * checksum[ 62 - i * 8 ] + 128 * checksum[ 63 - i * 8 ];
	}

	file.write( c_checksum, 8 );
}

unsigned long long CryptoEngine::calculateChecksum( ifstream & file )
{
	unsigned long long checksum = 0;
	if( !file.is_open() || !file.good() )
		return 0;

	file.seekg( 0 );
	char byte;

	while( file.get( byte ) )
	{
		checksum += static_cast<unsigned char>(byte);
	}
	checksum = ~checksum;
	file.clear();
	file.seekg( 0 );

	return checksum;
}

string CryptoEngine::getFileName( string & path )
{
	size_t pos1 = path.rfind( '\\' );
	size_t pos2 = path.rfind( '/' );
	size_t pos;
	if( pos1 == string::npos )
		pos = pos2;
	else if( pos2 == string::npos )
		pos = pos1;
	else if( pos1 > pos2 )
		pos = pos1;
	else
		pos = pos2;

	if( pos == string::npos )
		return path;

	string name = string( path.begin() + pos + 1, path.end() );
	return name;
}

bool CryptoEngine::signatureVerified( string signature )
{
	if( signature == string( "CRYPTER\0", 8 ) )
		return true;
	else
		return false;
}