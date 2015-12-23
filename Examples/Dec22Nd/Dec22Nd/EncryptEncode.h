#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <wincrypt.h>
#pragma comment(lib, "crypt32.lib")
#include <vector>
#include <string>
typedef unsigned char BYTE;

typedef struct  EncryptEncoder
{

	static std::string encode(const std::vector<BYTE>& buf);
	static std::string encode(const BYTE* buf, unsigned int bufLen);
	static std::vector<BYTE> decode(std::string encoded_string);
}  Decoder;
//std::string encoded = Encryptencoder::encode(pbCipherText, cbCipherText); // Using this code to transfer from BYTE to String! I could rewrite this later Dec 17th 2015: 
//	