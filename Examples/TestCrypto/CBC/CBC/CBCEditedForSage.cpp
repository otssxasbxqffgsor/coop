#include <cstdio>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <cstdlib>
using std::exit;

#include <string>
using std::string;

#include "..\cryptopp560\osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include "..\cryptopp560\cryptlib.h"
using CryptoPP::Exception;


#include "..\cryptopp560\filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "..\cryptopp560\des.h"
using CryptoPP::DES_EDE2;
using CryptoPP::ECB_Mode;



#include "..\cryptopp560\secblock.h"
using CryptoPP::SecByteBlock;


#include "..\cryptopp560\hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "..\cryptopp560\aes.h"
using CryptoPP::AES;

#include "..\cryptopp560\base64.h"
using CryptoPP::SimpleProxyFilter;
using CryptoPP::Base64Encoder;

#include "..\cryptopp560\basecode.h"



int main(int argc, char* argv[])
{
AutoSeededRandomPool prng;


	// Filling with actual key
	string plain = "ECB Mode Test";
	string cipher, encoded, recovered;
	unsigned char key[] = {35,101,45,114,65,119,114,117,55,33,63,95,65,99,114,117,109,
53,103,95,115,87,101,80,54,103,69,74,85,53,56,0};

	// Pretty print key
	std::cout<<"The Key is->"<<key<< endl;;
	/*********************************\
	\*********************************/

try
{
    cout << "plain text: " << plain << endl;

    ECB_Mode< AES >::Encryption e;
    e.SetKey( key, sizeof(key) );

    // The StreamTransformationFilter adds padding
    //  as required. ECB and CBC Mode must be padded
    //  to the block size of the cipher.
    StringSource ss1( plain, true, 
        new StreamTransformationFilter( e,
            new StringSink( cipher )
        ) // StreamTransformationFilter      
    ); // StringSource
}
catch( CryptoPP::Exception& e )
	{
    cerr << e.what() << endl;
    exit(1);
	}

/*********************************\
\*********************************/

// Pretty print cipher text
StringSource ss2( cipher, true,
    new Base64Encoder(
        new StringSink( encoded )
    ) // HexEncoder // Base64Encoder
); // StringSource
cout << "cipher text: " << encoded << endl;

/*********************************\
\*********************************/
// Decrypt
try
{
    ECB_Mode< AES >::Decryption d;
    // ECB Mode does not use an IV
    d.SetKey( key, sizeof(key) );

    // The StreamTransformationFilter removes
    //  padding as required.
    StringSource ss3( cipher, true, 
        new StreamTransformationFilter( d,
            new StringSink( recovered )
        ) // StreamTransformationFilter
    ); // StringSource

    cout << "recovered text: " << recovered << endl;
}
catch( CryptoPP::Exception& e )
{
    cerr << e.what() << endl;
    exit(1);
}


/*********************************\
\*********************************/


	return 0;
}

