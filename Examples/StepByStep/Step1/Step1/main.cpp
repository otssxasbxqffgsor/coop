#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <bcrypt.h>
#include "prddfun.h"
#include <assert.h> 

#define LenOfInput 4
#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)
#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)
#pragma comment(lib, "bcrypt.lib")



void __cdecl wmain(	int   argc,	__in_ecount(argc) LPWSTR *wargv)
{
	// --------------------------------------------------------------------------------------------------------------------------------//
	// ----------------------------------------------------SETTNGS--------------------------------------------------------------------//
	// --------------------------------------------------------------------------------------------------------------------------------//
	
	// This is the actual string
	const BYTE rgbPlaintext[4] = { 'T', 'E', 'S', 'T' };
	
	

	// length of the deceyption matrix 
	static const BYTE rgbIV[] =
	{
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
	};
	// Len of the Key should be 32 bytes
	BYTE rgbAES128Key[32];
	char key[] = "#e-rAwru7!?_Acrum5g_sWeP6gEJU58";

	// Bulding non NUll Terminated string Key
		char *prtToKey = key;
		int i = 0;
		while (*prtToKey != '\0')
		rgbAES128Key[i++] = *prtToKey++;
		rgbAES128Key[31] = '9';
	// --------------------------------------------------------------------------------------------------------------------------------//
		assert(*(rgbPlaintext + LenOfInput-1) == rgbPlaintext[LenOfInput - 1]);
		
	// --------------------------------------------------------------------------------------------------------------------------------//
	BCRYPT_ALG_HANDLE       hAesAlg = NULL;
	BCRYPT_KEY_HANDLE       hKey = NULL;
	NTSTATUS                status = STATUS_UNSUCCESSFUL;
	DWORD					cbCipherText = 0, cbPlainText = 0, cbData = 0, cbKeyObject = 0, cbBlockLen = sizeof(rgbIV), cbBlob = 0;
	PBYTE					pbCipherText = NULL, pbPlainText = NULL, pbKeyObject = NULL, pbIV=NULL,	pbBlob = NULL;


	// --------------------------------------------------------------------------------------------------------------------------------//
	// ------------------------------------END OF SETTINGS, START OF ENCRYPTION SEQUENCE----------------------------------------------//
	// --------------------------------------------------------------------------------------------------------------------------------//
	// Open an algorithm handle.
	if (!NT_SUCCESS(status = BCryptOpenAlgorithmProvider(&hAesAlg,BCRYPT_AES_ALGORITHM,NULL,0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
		goto Cleanup;
	}
	// --------------------------------------------------------------------------------------------------------------------------------//
	
	// Calculate the size of the buffer to hold the KeyObject.
	if (!NT_SUCCESS(status = BCryptGetProperty(hAesAlg,BCRYPT_OBJECT_LENGTH,(PBYTE)&cbKeyObject,sizeof(DWORD),&cbData,0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
		goto Cleanup;
	}
	// --------------------------------------------------------------------------------------------------------------------------------//

	// Allocate the key object on the heap.
	pbKeyObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbKeyObject);
	if (NULL == pbKeyObject)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}
	// --------------------------------------------------------------------------------------------------------------------------------//

	// Calculate the block length for the IV.
	//if (!NT_SUCCESS(status = BCryptGetProperty(	hAesAlg,BCRYPT_BLOCK_LENGTH,(PBYTE)&cbBlockLen,sizeof(DWORD),&cbData,0)))
	//{
	//	wprintf(L"**** Error 0x%x returned by BCryptGetProperty\n", status);
	//	goto Cleanup;
	//}
	// --------------------------------------------------------------------------------------------------------------------------------//

	//// Determine whether the cbBlockLen is not longer than the IV length.
	//if (cbBlockLen > sizeof(rgbIV))
	//{
	//	wprintf(L"**** block length is longer than the provided IV length\n");
	//	goto Cleanup;
	//}
	// --------------------------------------------------------------------------------------------------------------------------------//

	// Allocate a buffer for the IV. The buffer is consumed during the 
	// encrypt/decrypt process.
	pbIV = (PBYTE)calloc(cbBlockLen,sizeof(PBYTE));
	//if (NULL == pbIV)
	//{
	//	wprintf(L"**** memory allocation failed\n");
	//	goto Cleanup;
	//}
	//if (pbIV!=NULL) // Making sure memory was allocated 
		memcpy(pbIV, rgbIV, cbBlockLen);
	//else goto Cleanup;

	if (!NT_SUCCESS(status = BCryptSetProperty(hAesAlg,BCRYPT_CHAINING_MODE,(PBYTE)BCRYPT_CHAIN_MODE_CBC,sizeof(BCRYPT_CHAIN_MODE_CBC),0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptSetProperty\n", status);
		goto Cleanup;
	}


	// --------------------------------------------------------------------------------------------------------------------------------//

	// Generate the key from supplied input key bytes.
	if (!NT_SUCCESS(status = BCryptGenerateSymmetricKey(hAesAlg,&hKey,pbKeyObject,cbKeyObject,(PBYTE)rgbAES128Key,sizeof(rgbAES128Key),	0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptGenerateSymmetricKey\n", status);
		goto Cleanup;
	}

	// --------------------------------------------------------------------------------------------------------------------------------//

	// Save another copy of the key for later.
	if (!NT_SUCCESS(status = BCryptExportKey(hKey,NULL,BCRYPT_OPAQUE_KEY_BLOB,NULL,0,&cbBlob,0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptExportKey\n", status);
		goto Cleanup;
	}

	// --------------------------------------------------------------------------------------------------------------------------------//

	// Allocate the buffer to hold the BLOB.
	pbBlob = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbBlob);
	if (NULL == pbBlob)
	{
		wprintf(L"**** memory allocation failed\n");
		goto Cleanup;
	}

	if (!NT_SUCCESS(status = BCryptExportKey(hKey,NULL,BCRYPT_OPAQUE_KEY_BLOB,pbBlob,cbBlob,&cbBlob,0)))
	{
		wprintf(L"**** Error 0x%x returned by BCryptExportKey\n", status);
		goto Cleanup;
	}

	cbPlainText = sizeof(rgbPlaintext);
	pbPlainText = (PBYTE ) calloc(strlen((char*)rgbPlaintext), sizeof(PBYTE));
	//strcpy((char*)pbPlainText, (char*)cbPlainText);
	////	(PBYTE)HeapAlloc(GetProcessHeap(), 0, cbPlainText);
	//if (NULL == pbPlainText)
	//{
	//	wprintf(L"**** memory allocation failed\n");
	//	goto Cleanup;
	//}



	memcpy(pbPlainText, rgbPlaintext, cbPlainText);

	// Thus far pbPlainText has frou character without null 


	// --------------------------------------------------------------------------------------------------------------------------------//

	// Get the output buffer size.
	//int p = strlen((char *)pbIV);

	//if (!NT_SUCCESS(status = BCryptEncrypt(hKey,pbPlainText,cbPlainText,NULL,pbIV,cbBlockLen,NULL,0,&cbCipherText,BCRYPT_BLOCK_PADDING)))
	//{
	//	wprintf(L"**** Error 0x%x returned by BCryptEncrypt\n", status);
	//	goto Cleanup;
	//}

	//pbCipherText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbCipherText);
	//if (NULL == pbCipherText)
	//{
	//	wprintf(L"**** memory allocation failed\n");
	//	goto Cleanup;
	//}
	// --------------------------------------------------------------------------------------------------------------------------------//

	cbCipherText = cbPlainText;
	pbCipherText = (PBYTE)calloc(cbCipherText,sizeof(PBYTE));
	memcpy(pbCipherText, rgbPlaintext, cbPlainText);



	// Use the key to encrypt the plaintext buffer.
	// For block sized messages, block padding will add an extra block.
	//if (!NT_SUCCESS(status = BCryptEncrypt(	hKey,pbPlainText,cbPlainText,NULL,pbIV,cbBlockLen,pbCipherText,cbCipherText,&cbData,BCRYPT_BLOCK_PADDING)))
	//{
	//	wprintf(L"**** Error 0x%x returned by BCryptEncrypt\n", status);
	////	goto Cleanup;
	//}
	// --------------------------------------------------------------------------------------------------------------------------------//

	//// Destroy the key and reimport from saved BLOB.
	//if (!NT_SUCCESS(status = BCryptDestroyKey(hKey)))
	//{
	//	wprintf(L"**** Error 0x%x returned by BCryptDestroyKey\n", status);
	//	goto Cleanup;
	//}
	//hKey = 0;


	//pbPlainText = NULL;
	//// --------------------------------------------------------------------------------------------------------------------------------//

	//// We can reuse the key object.
	//memset(pbKeyObject, 0, cbKeyObject);

	//// --------------------------------------------------------------------------------------------------------------------------------//

	//// Reinitialize the IV because encryption would have modified it.
	//memcpy(pbIV, rgbIV, cbBlockLen);


	//if (!NT_SUCCESS(status = BCryptImportKey(hAesAlg,NULL,BCRYPT_OPAQUE_KEY_BLOB,&hKey,pbKeyObject,cbKeyObject,pbBlob,cbBlob,0)))
	//{
	//	wprintf(L"**** Error 0x%x returned by BCryptGenerateSymmetricKey\n", status);
	//	goto Cleanup;
	//}

	//// --------------------------------------------------------------------------------------------------------------------------------//

	////
	//// Get the output buffer size.
	////
	//if (!NT_SUCCESS(status = BCryptDecrypt(hKey,pbCipherText,cbCipherText,NULL,pbIV,cbBlockLen,NULL,0,&cbPlainText,	BCRYPT_BLOCK_PADDING)))
	//{
	//	wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
	//	goto Cleanup;
	//}

	//pbPlainText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbPlainText);


	//if (NT_SUCCESS(status = BCryptDecrypt(hKey,pbCipherText,cbCipherText,NULL,pbIV,cbBlockLen,pbPlainText,cbPlainText,&cbPlainText,BCRYPT_BLOCK_PADDING)))
	//{
	//	
	//	std::string encoded = Base64::encode(pbCipherText, cbCipherText); // Using this code to transfer from BYTE to String! I could rewrite this later Dec 17th 2015: 
	//	
	//	wprintf(L"Success\n");
	//}

	if (0 == memcmp(pbPlainText, (PBYTE)rgbPlaintext, sizeof(rgbPlaintext)))
	{
		
		wprintf(L"Expected decrypted text comparison successed!.\n");
	}

	wprintf(L"End of the main, Success!\n");

	// --------------------------------------------------------------------------------------------------------------------------------//
	// --------------------------------------------------------------------------------------------------------------------------------//
	// --------------------------------------------------------------------------------------------------------------------------------//
	// --------------------------------------------------------------------------------------------------------------------------------//
	// --------------------------------------------------------------------------------------------------------------------------------//
























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

