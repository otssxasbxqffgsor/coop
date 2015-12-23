#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <bcrypt.h>
#include "EncryptoCng.h"
#include <stdio.h>
#include <tchar.h>
#include <wincrypt.h>
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)

#pragma comment(lib, "crypt32.lib")
#define _BASE64_H_
#include <vector>
#include <string>
typedef unsigned char BYTE;



static const BYTE from_base64[] = { 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 62, 255, 62, 255, 63,
52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 255, 255, 0, 255, 255, 255,
255, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 255, 255, 255, 255, 63,
255, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 255, 255, 255, 255, 255 };

static const char to_base64[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

std::string Encypto::encode(const BYTE* buf, unsigned int bufLen)
{
	// Calculate how many bytes that needs to be added to get a multiple of 3
	size_t missing = 0;
	size_t ret_size = bufLen;
	while ((ret_size % 3) != 0)
	{
		++ret_size;
		++missing;
	}

	// Expand the return string size to a multiple of 4
	ret_size = 4 * ret_size / 3;

	std::string ret;
	ret.reserve(ret_size);

	for (unsigned int i = 0; i<ret_size / 4; ++i)
	{
		// Read a group of three bytes (avoid buffer overrun by replacing with 0)
		size_t index = i * 3;
		BYTE b3[3];
		b3[0] = (index + 0 < bufLen) ? buf[index + 0] : 0;
		b3[1] = (index + 1 < bufLen) ? buf[index + 1] : 0;
		b3[2] = (index + 2 < bufLen) ? buf[index + 2] : 0;

		// Transform into four base 64 characters
		BYTE b4[4];
		b4[0] = ((b3[0] & 0xfc) >> 2);
		b4[1] = ((b3[0] & 0x03) << 4) + ((b3[1] & 0xf0) >> 4);
		b4[2] = ((b3[1] & 0x0f) << 2) + ((b3[2] & 0xc0) >> 6);
		b4[3] = ((b3[2] & 0x3f) << 0);

		// Add the base 64 characters to the return value
		ret.push_back(to_base64[b4[0]]);
		ret.push_back(to_base64[b4[1]]);
		ret.push_back(to_base64[b4[2]]);
		ret.push_back(to_base64[b4[3]]);
	}

	// Replace data that is invalid (always as many as there are missing bytes)
	for (size_t i = 0; i<missing; ++i)
		ret[ret_size - i - 1] = '=';
	
	return ret;
}


std::string Encypto::Encrypt(char *_strInput, const int strLen){


#pragma comment(lib, "bcrypt.lib")

	if (!strLen == NULL && strLen != 0 || _strInput != NULL || *_strInput != '\0'){
		
		//--------Memory Managament Use this block to see how much memory has been allcoated locally------//
		int _lenOfBuf = 0;
		std::string encoded;


		BYTE *rgbPlaintext = (BYTE*)calloc(strLen, sizeof(BYTE));
		BYTE * _prtIntStr = (BYTE*)_strInput;
		BYTE *_prtTorgbPlaintext = rgbPlaintext;

		BYTE rgbAES128Key[32];

		static const BYTE rgbIV[] =
		{
			0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
			0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		};

		//------------------------------------------------------------------------------------------------//
		// --------------------------------------------- Building the key -------------------------------//
		//----------------------------------------------------------------------------------------------//

		char key[] = "#e-rAwru7!?_Acrum5g_sWeP6gEJU58";

		char *prtToKey = key;
		int i = 0;

		while (*prtToKey != '\0'){
			rgbAES128Key[i++] = *prtToKey++;
		}
		rgbAES128Key[31] = '9';

		//----------------------------------------------------------------------------------------------//
		//------building a non-null-terminated buffer to hold the text encryption ---------------------// 
		//----------------------------------------------------------------------------------------------//
		// Building a new Non terminate char array, cause tha tis the most importnatn parameter in the encryption, otherwise the complier will throw "a Given final block not properly padded" error 
		// Ver good tool to evaluate the string convertions, use this to evaluate your input and output http://8gwifi.org/CipherFunctions.jsp
		// This is an example of expected string 
		//"businessPartnerId=3;sourceCompanyCode=3;sourceProduct=Sage300;fein=3;ts=2015-12-21T19:52:58.041Z;ec=50;companyName=3;address1=3;address2=3;city=3;state=AK;zip=3;";

		while (_lenOfBuf < strLen)
		{

			if (*_prtIntStr != '\0' &&
				((int)*_prtIntStr == 59 ||
				(int)*_prtIntStr == 61 ||
				(int)*_prtIntStr == 45 ||
				(int)*_prtIntStr == 46 ||
				((int)*_prtIntStr >= 48 && (int)*_prtIntStr <= 58 ||
				(int)*_prtIntStr >= 67 && (int)*_prtIntStr <= 90 ||
				(int)*_prtIntStr >= 97 && (int)*_prtIntStr <= 122)))
			{

				*(_prtTorgbPlaintext++) = *(_prtIntStr++);
				_lenOfBuf++;
				std::cout << rgbPlaintext<<std::endl;
				std::cout << strlen((char *)rgbPlaintext) << std::endl;;

			}
			else _lenOfBuf++; //std::cout << _lenOfBuf << std::endl;;
			
		}

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
	/*	if (cbBlockLen > sizeof(rgbIV))
		{
			wprintf(L"**** block length is longer than the provided IV length\n");
			goto Cleanup;
		}
*/
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
			strlen((char*)rgbAES128Key),
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

		cbPlainText = strlen((char*)rgbPlaintext);
		pbPlainText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbPlainText);
		if (NULL == pbPlainText)
		{
			wprintf(L"**** memory allocation failed\n");
			goto Cleanup;
		}

		memcpy(pbPlainText, rgbPlaintext, strlen((char*)rgbPlaintext));

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
			encoded = Encypto::encode(pbCipherText, cbCipherText); // Using this code to transfer from BYTE to String! I could rewrite this later Dec 17th 2015: 
			std::cout << encoded << std::endl;
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
			//std::vector<BYTE> decoded = Base64::decode(encoded);
		//	wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
			//goto Cleanup;
		}

		//https://pgmorww11v.paigroup.corp/DDP.Web/Home/SageDirectDepositApplication?key=0QRHBeZ4CKGpik2KnBpNlUAwZ9aL9BVUaTpKqJE%2FeCYTdYKw5NUVUhwiqvaZfHFkUrsK4vOVxDwGI0XUQVQ1deS6MyOdvktn2rhhaloVd0uAtDd5mhhnI4qtvtTQg%2Bklqpc3q8qDo%2BvfCGwY%2FMv%2Bkt%2BBcNm0fDlmh6aunrVeXSile4P%2BCUybXgEowfkpqD4U6Ws5pd1N2PWQuMsuslxMGSYRg4dImTu4LSjIT5xGIfE%3D&sourceErp=Sage300


		if (0 == memcmp(pbPlainText, (PBYTE)rgbPlaintext, strlen((char*)rgbPlaintext)))
		{

			return &encoded[0];
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

		//---------------//
	
	}
	else return false;
};
std::string Encypto::Dencrypt(char *_strInput, int strLen){
	return _strInput;
};

