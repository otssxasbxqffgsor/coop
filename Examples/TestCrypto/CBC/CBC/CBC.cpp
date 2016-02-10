#include "stdafx.h"



//:::::::: Standard C++ Libs ::://
#include <windows.h>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#include <string>
using std::string;
#include <cstdlib>
using std::exit;
#include <cstdio>
using std::cout;
using std::cerr;
using std::endl;

//:::::::: Crypto ++ Libs ::://
#include "..\cryptopp560\osrng.h"
using CryptoPP::AutoSeededRandomPool;
#include "..\cryptopp560\cryptlib.h"
//using CryptoPP::Exception;
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

using CryptoPP::ECB_Mode;
#include "..\cryptopp560\secblock.h"
using CryptoPP::SecByteBlock;
#include"..\cryptopp560\filters.h"
#include "..\cryptopp560\aes.h"
using CryptoPP::AES;
#include "..\cryptopp560\base64.h"
using CryptoPP::SimpleProxyFilter;
using CryptoPP::Base64Encoder;
using CryptoPP::Base64Decoder;
using CryptoPP::Base64URLEncoder;
using CryptoPP::Base64URLDecoder;
#include "..\cryptopp560\pch.h"

string urlEncode(string str){
    string new_str = "";
    char c;
    int ic;
    const char* chars = str.c_str();
    char bufHex[10];
    int len = strlen(chars);

    for(int i=0;i<len;i++){
        c = chars[i];
        ic = c;
        // uncomment this if you want to encode spaces with +
        /*if (c==' ') new_str += '+';   
        else */if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') new_str += c;
        else {
            sprintf(bufHex,"%X",c);
            if(ic < 16) 
                new_str += "%0"; 
            else
                new_str += "%";
            new_str += bufHex;
        }
    }
    return new_str;
 }







int main(){


		//char _unEncryptedUrl [_urlLen+1];
	//strcpy_s(_unEncryptedUrl, _urlLen, _url);
	
	//AutoSeededRandomPool prng;
	char _url[] = "businessPartnerId=1234;sourceCompanyCode=123;sourceProduct=Sage300;fein=123;ts=2016-01-15T00:21:52.252Z;ec=50;companyName=kian;address1=kian;address2=kian;city=kian;state=AK;zip=Kian;";	
	int _urlLen = sizeof(_url);
	string plain(_url,_urlLen);
	//string plain = "businessPartnerId=123;sourceCompanyCode=123;sourceProduct=Sage300;fein=123;ts=2016-01-14T00:21:52.252Z;ec=50;companyName=kian;address1=kian;address2=kian;city=kian;state=AK;zip=Kian;";	
	string cipher, encoded, recovered;
	unsigned char key[] = {35,101,45,114,65,119,114,117,55,33,63,95,65,99,114,117,109,53,103,95,115,87,101,80,54,103,69,74,85,53,56,0};
	
	string Sage300prefix = "https://pgmorww11v.paigroup.corp/DDP.Web/Home/Sage300/?key=";
    // Build Encyption 
	
	

//	byte key[AES::DEFAULT_KEYLENGTH];
	//prng.GenerateBlock(key, sizeof(key));

	//string plain = "ECB Mode Test";
//	string cipher, encoded, recovered;

	/*********************************\
	\*********************************/

	// Pretty print key
	encoded.clear();
	/*StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;
*/

		ECB_Mode< AES >::Encryption e;
		e.SetKey(key, sizeof(key));
	
	// Use encryption and Padding
     StringSource ss1( plain, true, 
         new StreamTransformationFilter( e,
             new StringSink( cipher ),
			 StreamTransformationFilter::PKCS_PADDING
         ) // StreamTransformationFilter      
     ); // StringSource
	
	 // Base64Eecoder	
	StringSource ss2( cipher, true,
		new Base64Encoder(
			new StringSink( encoded )
    ) // HexEncoder // Base64Encoder
	);

Sage300prefix = Sage300prefix+urlEncode(encoded);

return 0;

};


