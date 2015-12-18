
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <bcrypt.h>

#include "prddfun.h"
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)


//#define DATA_TO_ENCRYPT  "businessPartnerId=12;sourceCompanyCode=12;sourceProduct=Sage300;fein=12;ts=2015-12-11T23:41:38.700Z;ec=50;companyName=;address1=;address2=;city=;state=;zip=;"
//#define DATA_KEY_ENCRYPTION "#e-rAwru7!?_acrum5g_sWeP6gEJU58\0"

#pragma comment(lib, "bcrypt.lib")


const BYTE rgbPlaintext[] =
//"TestMe";
//"businessPartnerId=2;sourceCompanyCode=2;sourceProduct=Sage300;fein=2;ts=2015-12-16T23:07:42.710Z;ec=50;companyName=2;address1=2;address2=2;city=2;state=AK;zip=2;";
"businessPartnerId=33;sourceCompanyCode=33;sourceProduct=Sage100;fein=33;ts=2015-12-18T02:30:25.701Z;ec=50;";
//{
//	0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
//};

static const BYTE rgbIV[] =
{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
};

  BYTE rgbAES128Key[32];

char key[] = "#e-rAwru7!?_acrum5g_sWeP6gEJU58";

//static const BYTE rgbAES128Key[32] = {'#','e','-','r','A','w','r','u','7','!',
//'?','_','a','c','r','u','m','5','g','_','s','W','e','P','6','g','E','J','U','5','8',NULL};
//{
//	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
//	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
//};
//
//{
//	0x35,0x101,0x45,
//	0x114,0x65,0x119,0x14,0x117,0x55,0x33,0x63,0x95,0x97,
//	0x99,0x114,0x117,0x109,0x53,0x103,0x95,0x115,0x87,0x101,
//	0x80, 0x54, 0x103, 0x69, 0x74, 0x85, 0x53, 0x56, 0x0 
//};

//
//{
//	'35', '101', '45',
//		'14', '65', '119','14','117', '55', '33', '63', '95', '97',
//		'99', '114','117', '109', '53', '103', '95', '115', '87', '101',
//		'80', '54', '103', '69', '74', '85', '53', '56', '0'
//};
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

//// Convert the String Key to Byte Array to avoid the stupid \0 as a part of the key
//// What \0 is part of the Key? It is stupid! but reality!
//std::string UriEncode(const std::string & sSrc)
//{
//	const char DEC2HEX[16 + 1] = "0123456789ABCDEF";
//	const unsigned char * pSrc = (const unsigned char *)sSrc.c_str();
//	const int SRC_LEN = sSrc.length();
//	unsigned char * const pStart = new unsigned char[SRC_LEN * 3];
//	unsigned char * pEnd = pStart;
//	const unsigned char * const SRC_END = pSrc + SRC_LEN;
//
//
//
//	if (('a' < *pSrc &&*pSrc <= 'z') ||
//		('A' <= *pSrc && *pSrc <= 'Z') ||
//		('0' <= *pSrc && *pSrc <= '9')){
//		*pEnd++ = *pSrc;
//		}
//else
//		{
//			// escape this char
//			*pEnd++ = '%';
//			*pEnd++ = DEC2HEX[*pSrc >> 4];
//			*pEnd++ = DEC2HEX[*pSrc & 0x0F];
//		}
//
//	std::string sResult((char *)pStart, (char *)pEnd);
//	delete[] pStart;
//	return sResult;
//}

void __cdecl wmain(
	int                      argc,
	__in_ecount(argc) LPWSTR *wargv)
{
	char *prtToKey = key;
	int i = 0; 

	while (*prtToKey != '\0'){
		rgbAES128Key[i++] = *prtToKey++;
		
	}
	rgbAES128Key[31] = '\0';


	BCRYPT_ALG_HANDLE       hAesAlg = NULL;
	BCRYPT_KEY_HANDLE       hKey = NULL;
	NTSTATUS                status = STATUS_UNSUCCESSFUL;
	DWORD                   cbCipherText = 0,
		cbPlainText = 0,
		cbData = 0,
		cbKeyObject = 0,
		cbBlockLen = 0,
		cbBlob = 0;
	PBYTE                   pbCipherText = NULL,
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
		wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
		goto Cleanup;
	}

	// Determine whether the cbBlockLen is not longer than the IV length.
	if (cbBlockLen > sizeof(rgbIV))
	{
		wprintf(L"**** block length is longer than the provided IV length\n");
		goto Cleanup;
	}

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
	if (!NT_SUCCESS(status = BCryptDecrypt(
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
		wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
		goto Cleanup;
	}

	pbPlainText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbPlainText);
	/*if (NULL == pbPlainText)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}*/

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
		/*char DEC2HEX[16 + 1] = "0123456789ABCDEF";

		BYTE buf[] = "ABCD";*/
		std::string encoded = Base64::encode(pbCipherText, cbCipherText);
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
		wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
		//goto Cleanup;
	}

	//https://pgmorww11v.paigroup.corp/DDP.Web/Home/SageDirectDepositApplication?key=0QRHBeZ4CKGpik2KnBpNlUAwZ9aL9BVUaTpKqJE%2FeCYTdYKw5NUVUhwiqvaZfHFkUrsK4vOVxDwGI0XUQVQ1deS6MyOdvktn2rhhaloVd0uAtDd5mhhnI4qtvtTQg%2Bklqpc3q8qDo%2BvfCGwY%2FMv%2Bkt%2BBcNm0fDlmh6aunrVeXSile4P%2BCUybXgEowfkpqD4U6Ws5pd1N2PWQuMsuslxMGSYRg4dImTu4LSjIT5xGIfE%3D&sourceErp=Sage300


	if (0 == memcmp(pbPlainText, (PBYTE)rgbPlaintext, sizeof(rgbPlaintext)))
	{
		const BYTE* str1 = pbPlainText;
		int len = strlen(reinterpret_cast<const char*>(str1));
		std::string str2(str1, str1 + len);
		std::cout<<( str2);
		wprintf(L"Expected decrypted text comparison successed!.\n");
	//	goto Cleanup;
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

