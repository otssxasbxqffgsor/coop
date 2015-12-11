// Encryption101.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdio.h>
#include <bcrypt.h>

//#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

//#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)


#define DATA_TO_ENCRYPT  "Test Data"



int main()
{

	//BCRYPT_ALG_HANDLE       hAesAlg = NULL;


	printf("test");
	BCryptOpenAlgorithmProvider(NULL,NULL,NULL,0);	




	//BCRYPT_KEY_HANDLE       hKey = NULL;
	//NTSTATUS                status = STATUS_UNSUCCESSFUL;
//	DWORD                   cbCipherText = 0,
//		cbPlainText = 0,
//		cbData = 0,
//		cbKeyObject = 0,
//		cbBlockLen = 0,
//		cbBlob = 0;
//	PBYTE                   pbCipherText = NULL,
//		pbPlainText = NULL,
//		pbKeyObject = NULL,
//		pbIV = NULL,
//		pbBlob = NULL;

	//UNREFERENCED_PARAMETER(argc);
	//UNREFERENCED_PARAMETER(argv);


	// Open an algorithm handle.
	//BCryptOpenAlgorithmProvider(
//		NULL,
//		NULL,
//		NULL,
//		0);	
	/*
	{
	//	printf("**** Error 0x%x returned by BCryptOpenAlgorithmProvider\n", status);
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
	if (NULL == pbPlainText)
	{
	wprintf(L"**** memory allocation failed\n");
	goto Cleanup;
	}

	if (!NT_SUCCESS(status = BCryptDecrypt(
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
	wprintf(L"**** Error 0x%x returned by BCryptDecrypt\n", status);
	goto Cleanup;
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
	*/
	return 0;
}


