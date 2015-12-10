#include <windows.h>
#include "Wincrypt.h"
#include "stdio.h"

int main()
{
	HCRYPTPROV hCryptProv = NULL;
	if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		printf("CryptoAPI working\n\n");
		exit(0);
	}
	else
	{
		printf("Error 0x%.8x", GetLastError());
		exit(1);
	}
}