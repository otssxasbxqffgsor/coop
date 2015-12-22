#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <bcrypt.h>


typedef struct CngEncryption{
	std::string Encrypt(char *_strInput, const int strLen);
	std::string Dencrypt(char *_strInput, int strLen);
	std::string encode(const BYTE* buf, unsigned int bufLen);
	
}Encypto;