#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* MCrypt API available online:
* http://linux.die.net/man/3/mcrypt
*/
#include <mcrypt.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

i



}

int main()
{
	utoSeededRandomPool rnd;

	// Generate a random key
	SecByteBlock key(0x00, AES::DEFAULT_KEYLENGTH);
	rnd.GenerateBlock(key, key.size());

	// Generate a random IV
	byte iv[AES::BLOCKSIZE];
	rnd.GenerateBlock(iv, AES::BLOCKSIZE);

	char plainText[] = "Hello! How are you.";
	int messageLen = (int)strlen(plainText) + 1;

	//////////////////////////////////////////////////////////////////////////
	// Encrypt

	CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), iv);
	cfbEncryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);

	//////////////////////////////////////////////////////////////////////////
	// Decrypt

	CFB_Mode<AES>::Decryption cfbDecryption(key, key.size(), iv);
	cfbDecryption.ProcessData((byte*)plainText, (byte*)plainText, messageLen);

	return 0;
}