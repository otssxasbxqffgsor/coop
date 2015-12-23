#include "stdafx.h"

// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
#include <cstdio>
#include <iostream>
#include "..\cryptopp560\osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "..\cryptopp560\cryptlib.h"
using CryptoPP::Exception;

#include "..\cryptopp560\hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "..\cryptopp560\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "..\cryptopp560\des.h"
using CryptoPP::DES_EDE2;

#include "..\cryptopp560\modes.h"
using CryptoPP::CBC_Mode;

#include "..\cryptopp560\secblock.h"
using CryptoPP::SecByteBlock;
#include <iostream>
#include <string>
#include "..\cryptopp560\modes.h"
#include "..\cryptopp560\aes.h"
#include"..\cryptopp560\filters.h"


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "..\cryptopp560\cryptlib.h"
using CryptoPP::Exception;

#include "..\cryptopp560\hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
//using CryptoPP::Base64Encoder;
#include "..\cryptopp560\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "..\cryptopp560\aes.h"
using CryptoPP::AES;

#include "..\cryptopp560\modes.h"
using CryptoPP::ECB_Mode;

#include "..\\cryptopp560\base64.h"
using CryptoPP::SimpleProxyFilter;
using CryptoPP::Base64Encoder;



/*
CryptoPP::SecByteBlock HexDecodeString(const char *hex)
{
CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
CryptoPP::SecByteBlock result((size_t)ss.MaxRetrievable());
ss.Get(result, result.size());
return result;
}*/


int main(int argc, char* argv[])
{
	AutoSeededRandomPool prng;
	
	byte key[AES::DEFAULT_KEYLENGTH];
	prng.GenerateBlock(key, sizeof(key));

	string plain = "ECB Mode Test";
	string cipher, encoded, recovered;

	/*********************************\
	\*********************************/

	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		cout << "plain text: " << plain << endl;

		ECB_Mode< AES >::Encryption e;
		e.SetKey(key, sizeof(key));

		// The StreamTransformationFilter adds padding
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource(plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			) // StreamTransformationFilter      
		); // StringSource
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	// Pretty print
	encoded.clear();
	
StringSource(cipher, true,
		new Base64Encoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "cipher text: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		ECB_Mode< AES >::Decryption d;
		d.SetKey(key, sizeof(key));

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true, 
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource

		cout << "recovered text: " << recovered << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	return 0;
}

