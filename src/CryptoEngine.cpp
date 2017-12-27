#pragma once
#include "CryptoEngine.h"
#include <iostream>

using namespace std;

void CryptoEngine::encryptFiles( Command & cmd )
{
	// Nie ma przynajmniej 2 argument�w: has�o + plik
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
	// Nie ma przynajmniej 2 argument�w: has�o + plik
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
		// ------ POPRAWNO�� DESZYFRACJI ------- //
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

    file.seekg( 0 );    // Ustaw wska�nik czytania na pocz�tek pliku
    char signature[ 8 ];
    file.read( signature, 8 );  // Odczytaj 8 bajt�w
    
    if( !file.good() )  // Wyst�pi� b��d, np. koniec pliku
    {
        header.signature = "";
        file.clear();
        return header;
    }

    header.signature = string( signature, 8 );

    unsigned char c_checksum[ 8 ];
    file.read( (char*)c_checksum, 8 );

    if( !file.good() )  // Wyst�pi� b��d, np. koniec pliku
    {
        header.signature = "";
        file.clear();
        return header;
    }

	// parsowanie bajt�w z tablicy c_checksum na liczb� long long
    unsigned long long checksum = 0;
    for( int i = 0; i <= 6; i++ )
        checksum = (checksum | (unsigned char)c_checksum[ i ]) << 8;
    checksum = (checksum | (unsigned char)c_checksum[ 7 ]);

	// Niejawna konwersja z long long do bitset<64>
	// rozbija liczb� long long na pojedyncze bity.
	// Najmniej znacz�cy bit to header.checksum[ 0 ].
    header.checksum = checksum;

    return header;
}

void CryptoEngine::writeHeader( Header header, ofstream & file )
{
	file.write( header.signature.c_str(), 8 );
	bitset<64> checksum( header.checksum );

	// Przepisywanie 64 bit�w na tablic� 8 bajt�w
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