#pragma once
#include "CryptoEngine.h"
#include <iostream>

using namespace std;

//TODO encryptFiles
void CryptoEngine::encryptFiles( string& key, vector< string >& paths )
{
	cout << "Szyfrowanie " << paths.size() << " plikow haslem: " << key << endl;
	for( auto x : paths )
		cout << x << endl;
}

//TODO decryptFiles
void CryptoEngine::decryptFiles( string& key, vector< string >& paths )
{
	cout << "Odszyfrowywanie " << paths.size() << " plikow haslem: " << key << endl;
	for( auto x : paths )
		cout << x << endl;
}

// TODO analyzeFiles
void CryptoEngine::analyzeFiles( vector< string >& paths )
{
	cout << "Analiza " << paths.size() << " plikow:" << endl;
	for( auto x : paths )
		cout << x << endl;
}

// TODO autoCryption
void CryptoEngine::autoCryption( string & password, vector< string > & paths )
{
	cout << "Autoszyfrowanie " << paths.size() << " plikow:" << endl;
	for( auto x : paths )
		cout << x << endl;
}