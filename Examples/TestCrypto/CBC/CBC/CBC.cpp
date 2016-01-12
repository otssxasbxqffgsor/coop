#include "stdafx.h"

// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
#include <windows.h>
#include <cstdio>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
#include "..\cryptopp560\osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include <cstdlib>
using std::exit;
#include "..\cryptopp560\modes.h"
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

#include "..\\cryptopp560\base64.h"
using CryptoPP::SimpleProxyFilter;
using CryptoPP::Base64Encoder;
using CryptoPP::Base64Decoder;
using CryptoPP::Base64URLEncoder;
using CryptoPP::Base64URLDecoder;
#include "..\\cryptopp560\pch.h"

string UriEncode(const string & sSrc)
{
   const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
   const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
   const int SRC_LEN = sSrc.length();
   unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
   unsigned char * pEnd = pStart;
   const unsigned char * const SRC_END = pSrc + SRC_LEN;

   for (; pSrc < SRC_END; ++pSrc)
   {
      if (*pSrc) 
         *pEnd++ = *pSrc;
      else
      {
         // escape this char
         *pEnd++ = '%';
         *pEnd++ = DEC2HEX[*pSrc >> 4];
         *pEnd++ = DEC2HEX[*pSrc & 0x0F];
      }
   }

   string sResult((char *)pStart, (char *)pEnd);
   delete [] pStart;
   return sResult;
}



int main(int argc, char* argv[])
{
AutoSeededRandomPool prng;


	// Filling with actual key
	//string plain = "businessPartnerId=3;sourceCompanyCode=3;sourceProduct=Sage300;fein=3;ts=2015-12-21T19:59:06.812Z;ec=50;companyName=3;address1=3;address2=3;city=3;state=AK;zip=3;";
	 string plain = "businessPartnerId=22;sourceCompanyCode=22;sourceProduct=Sage100;fein=22;ts=2016-12-24T00:36:35.284Z;ec=0;";	
//string plain = "TestMeThisIsAGoodNews";
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
            new StringSink( cipher ),
			StreamTransformationFilter::PKCS_PADDING
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

/********************Base64URLEncoder*************\
\*********************Base64Decoder************/
string url;
string urlEn =    encoded;
string HttpUrl;
StringSource ss(urlEn, true,
    new Base64URLEncoder(
        new StringSink(url)
    ) // Base64URLDecoder
); // StringSource
 

HttpUrl = "https://pgmorww11v.paigroup.corp/DDP.Web/Home/Sage100/?key="+url;

/********************Base64URLEncoder*************\
\*********************Base64Decoder************/
urlEn = UriEncode(encoded);
HttpUrl = "https://pgmorww11v.paigroup.corp/DDP.Web/Home/Sage100/?key="+urlEn;

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



	return 0;
}

