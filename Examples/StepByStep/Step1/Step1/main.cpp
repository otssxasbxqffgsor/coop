


#include <windows.h>
#include <stdio.h>
#include <bcrypt.h>
#include "prddfun.h"
#include <iostream>
#pragma comment(lib, "bcrypt.lib")
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)


#define DATA_TO_ENCRYPT  "businessPartnerId=3;sourceCompanyCode=3;sourceProduct=Sage300;fein=3;ts=2015-12-21T19:59:06.812Z;ec=50;companyName=3;address1=3;address2=3;city=3;state=AK;zip=3;"
//#define DATA_KEY_ENCRYPTION "#e-rAwru7!?_acrum5g_sWeP6gEJU589"

//#define DATA_TO_ENCRYPT  "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" --> This does not have any affect on the output
//#define DATA_KEY_ENCRYPTION "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"



<<<<<<< HEAD
const BYTE rgbPlaintext[] = "Test";
	//"businessPartnerId=22;sourceCompanyCode=22;sourceProduct=Sage100;fein=22;ts=2015-12-19T01:52:50.983Z;ec=50;";
=======

const BYTE rgbPlaintext[] = "Te";//";//"businessPartnerId = 3; sourceCompanyCode = 3; sourceProduct = Sage300; fein = 3; ts = 2015 - 12 - 21T19:59 : 06.812Z; ec = 50; companyName = 3; address1 = 3; address2 = 3; city = 3; state = AK; zip = 3; ";
>>>>>>> Dev
//{
//	0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48,
//	0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48,
//	0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48,
//	0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48, 0x48,
//};

static const BYTE rgbIV[32] = 
{
	0x00, 0x01, 0x02, 0x03,  0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
	0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,

<<<<<<< HEAD
  BYTE rgbAES128Key[32];

char key[] = "#e-rAwru7!?_Acrum5g_sWeP6gEJU58";

//static const BYTE rgbAES128Key[32] = {'#','e','-','r','A','w','r','u','7','!',
//'?','_','a','c','r','u','m','5','g','_','s','W','e','P','6','g','E','J','U','5','8',NULL};
//{
//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
//};
//
=======
	
};
char key[] = "123456789013246578901323";
static  BYTE rgbAES128Key[24];
>>>>>>> Dev
//{
//	0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
//	0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
//		0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
//		0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30 };

void PrintBytes(
	IN BYTE     *pbPrintData,
	IN DWORD    cbDataLen)
{
	DWORD dwCount = 0;

	for (dwCount = 0; dwCount < cbDataLen; dwCount++)
	{
		printf("0x%02x, ", pbPrintData[dwCount]);

		if (0 == (dwCount + 1) % 10) putchar('\n');
	}

}

void __cdecl wmain(
	int                      argc,
	__in_ecount(argc) LPWSTR *wargv)
{
	char *prtToKey = key;
	int i = 0;

	while (*prtToKey != '\0'){
		rgbAES128Key[i++] = *prtToKey++;

	}
//	rgbAES128Key[23] = {NULL};
	// get length of the string 
	// build a new strign that has the 
	
	const BYTE rgbPlaintext[2] = { 'T', 'e' };
	



	BCRYPT_ALG_HANDLE       hAesAlg = NULL;
	BCRYPT_KEY_HANDLE       hKey = NULL;

	NTSTATUS                status = STATUS_UNSUCCESSFUL;
	DWORD                   cbCipherText = 0,
		cbPlainText = 0,
		cbData = 0,
		cbKeyObject = 0,
		cbBlockLen = 0,
		cbBlob = 0;
	PBYTE                   pbCipherText =NULL,
		pbPlainText = NULL,
		pbKeyObject = NULL,
		pbIV = NULL,
		pbBlob = NULL;

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(wargv);


	// Open an algorithm handle.
	if (!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(
		&hAesAlg,
		BCRYPT_AES_ALGORITHM,
		NULL,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
		goto Cleanup;
	}

	// Calculate the size of the buffer to hold the KeyObject.
	if (!NT_SUCCESS(status = BCryptGetProperty(
		hAesAlg,
		BCRYPT_OBJECT_LENGTH,
		(PBYTE)&cbKeyObject,
		sizeof(DWORD),
		&cbData,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
		goto Cleanup;
	}

	// Allocate the key object on the heap.
	pbKeyObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbKeyObject);
	if (NULL == pbKeyObject)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	// Calculate the block length for the IV.
	if (!NT_SUCCESS(status = BCryptGetProperty(
		hAesAlg,
		BCRYPT_BLOCK_LENGTH,
		(PBYTE)&cbBlockLen,
		sizeof(DWORD),
		&cbData,
		0)))
	{
		std::string encoded = Base64::encode(pbCipherText, cbCipherText);
		std::cout << encoded;
		wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
		goto Cleanup;
	}

	// Determine whether the cbBlockLen is not longer than the IV length.
	//if (cbBlockLen > sizeof(rgbIV))
	//{
	//	wprintf(L"**** block length is longer than the provided IV length\n");
	//	goto Cleanup;
	//}

	// Allocate a buffer for the IV. The buffer is consumed during the 
	// encrypt/decrypt process.
	pbIV = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbBlockLen);
	if (NULL == pbIV)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	memcpy(pbIV, rgbIV, cbBlockLen);

	if (!NT_SUCCESS(status = BCryptSetProperty(
		hAesAlg,
		BCRYPT_CHAINING_MODE,
		(PBYTE)BCRYPT_CHAIN_MODE_CBC,
		sizeof(BCRYPT_CHAIN_MODE_CBC),
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptSetProperty\n", status);
		goto Cleanup;
	}



	// Generate the key from supplied input key bytes.
	if (!NT_SUCCESS(status = BCryptGenerateSymmetricKey(
		hAesAlg,
		&hKey,
		pbKeyObject,
		cbKeyObject,
		(PBYTE)rgbAES128Key,
		sizeof(rgbAES128Key),
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptGenerateSymmetricKey\n", status);
		goto Cleanup;
	}


	// Save another copy of the key for later.
	if (!NT_SUCCESS(status = BCryptExportKey(
		hKey,
		NULL,
		BCRYPT_OPAQUE_KEY_BLOB,
		NULL,
		0,
		&cbBlob,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptExportKey\n", status);
		goto Cleanup;
	}


	// Allocate the buffer to hold the BLOB.
	pbBlob = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbBlob);
	if (NULL == pbBlob)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	if (!NT_SUCCESS(status = BCryptExportKey(
		hKey,
		NULL,
		BCRYPT_OPAQUE_KEY_BLOB,
		pbBlob,
		cbBlob,
		&cbBlob,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptExportKey\n", status);
		goto Cleanup;
	}

	cbPlainText = sizeof(rgbPlaintext);
	pbPlainText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbPlainText);
	if (NULL == pbPlainText)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	memcpy(pbPlainText, rgbPlaintext, sizeof(rgbPlaintext));

	//
	// Get the output buffer size.
	//
	if (!NT_SUCCESS(status = BCryptEncrypt(
		hKey,
		pbPlainText,
		cbPlainText,
		NULL,
		pbIV,
		cbBlockLen,
		NULL,
		0,
		&cbCipherText,
		BCRYPT_BLOCK_PADDING)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptEncrypt\n", status);
		goto Cleanup;
	}

	pbCipherText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbCipherText);
	if (NULL == pbCipherText)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	// Use the key to encrypt the plaintext buffer.
	// For block sized messages, block padding will add an extra block.
	if (!NT_SUCCESS(status = BCryptEncrypt(
		hKey,
		pbPlainText,
		cbPlainText,
		NULL,
		pbIV,
		cbBlockLen,
		pbCipherText,
		cbCipherText,
		&cbData,
		BCRYPT_BLOCK_PADDING)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptEncrypt\n", status);
		goto Cleanup;
	}

	// Destroy the key and reimport from saved BLOB.
	if (!NT_SUCCESS(status = BCryptDestroyKey(hKey)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptDestroyKey\n", status);
		goto Cleanup;
	}
	hKey = 0;

	if (pbPlainText)
	{
		HeapFree(GetProcessHeap(), 0, pbPlainText);
	}

	pbPlainText = NULL;

	// We can reuse the key object.
	memset(pbKeyObject, 0, cbKeyObject);


	// Reinitialize the IV because encryption would have modified it.
	memcpy(pbIV, rgbIV, cbBlockLen);


	if (!NT_SUCCESS(status = BCryptImportKey(
		hAesAlg,
		NULL,
		BCRYPT_OPAQUE_KEY_BLOB,
		&hKey,
		pbKeyObject,
		cbKeyObject,
		pbBlob,
		cbBlob,
		0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptGenerateSymmetricKey\n", status);
		goto Cleanup;
	}


	//
	// Get the output buffer size.
	//
	if (NT_SUCCESS(status = BCryptDecrypt(
		hKey,
		pbCipherText,
		cbCipherText,
		NULL,
		pbIV,
		cbBlockLen,
		NULL,
		0,
		&cbPlainText,
		BCRYPT_BLOCK_PADDING)))
	{
		
		std::string textWasEncoded = Base64::encode(pbCipherText, cbCipherText);
		std::cout << textWasEncoded<<std::endl;
		//wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
		//goto Cleanup;
	}

	pbPlainText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbPlainText);
	if (NULL == pbPlainText)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	if (NT_SUCCESS(status = BCryptDecrypt(
		hKey,
		pbCipherText,
		cbCipherText,
		NULL,
		pbIV,
		cbBlockLen,
		pbPlainText,
		cbPlainText,
		&cbPlainText,
		BCRYPT_BLOCK_PADDING)))
	{
<<<<<<< HEAD
		/*char DEC2HEX[16 + 1] = "0123456789ABCDEF";

		BYTE buf[] = "ABCD";*/
		std::string encoded = Base64::encode(pbCipherText, cbCipherText); // Using this code to transfer from BYTE to String! I could rewrite this later Dec 17th 2015: 
		/*std::string NoEncoded = encoded;*/
	//-->	UriEncode(encoded);
	//	char *r = curl_escape(_prtCipher, cbCipherText);

		//unsigned char *_prtCipher = pbCipherText;
		//int _lenCipher = cbCipherText;
		//while (_lenCipher >= 0){
		//	if (('a' < *_prtCipher &&*_prtCipher <= 'z') || 
		//		('A' <= *_prtCipher && *_prtCipher <= 'Z') ||
		//		('0' <= *_prtCipher && *_prtCipher <= '9')){
		//	// Do nothing 
		//	}
		//	else {
		//		*_prtCipher = '%';
		//		*_prtCipher = _prtCipher[*_prtCipher >> 4];
		//		*_prtCipher = _prtCipher[*_prtCipher & 0x0F];
		//	}
		//	_lenCipher--;
		//
		//}
		//
		// encoded = "QUJDRA=="
		std::vector<BYTE> decoded = Base64::decode(encoded);
=======
		
		std::cout << pbPlainText;
>>>>>>> Dev
		wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
		//goto Cleanup;
	}


	if (0 != memcmp(pbPlainText, (PBYTE)rgbPlaintext, sizeof(rgbPlaintext)))
	{
		wprintf(L"Expected decrypted text comparison failed.\n");
		goto Cleanup;
	}

	wprintf(L"Success!\n");


Cleanup:

	if (hAesAlg)
	{
		BCryptCloseAlgorithmProvider(hAesAlg, 0);
	}

	if (hKey)
	{
		BCryptDestroyKey(hKey);
	}

	if (pbCipherText)
	{
		HeapFree(GetProcessHeap(), 0, pbCipherText);
	}

	if (pbPlainText)
	{
		HeapFree(GetProcessHeap(), 0, pbPlainText);
	}

	if (pbKeyObject)
	{
		HeapFree(GetProcessHeap(), 0, pbKeyObject);
	}

	if (pbIV)
	{
		HeapFree(GetProcessHeap(), 0, pbIV);
	}

}

