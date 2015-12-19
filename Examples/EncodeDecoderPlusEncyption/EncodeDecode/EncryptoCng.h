#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <bcrypt.h>


typedef struct CngEncryption{
	char *Encrypt(char *_strInput, int strLen);
	char *Dencrypt(char *_strInput, int strLen);
}Encypto;