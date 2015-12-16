// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) Microsoft. All rights reserved.
/*++

Abstract:
Sample program for AES-CBC encryption using CNG

--*/



#include <windows.h>
#include <stdio.h>
#include <bcrypt.h>

#define NT_SUCCESS(Status)          (((NTSTATUS)(Status)) >= 0)

#define STATUS_UNSUCCESSFUL         ((NTSTATUS)0xC0000001L)





#pragma comment(lib, "bcrypt.lib")

// Encrypted Data
const BYTE rgbPlaintext[] = "businessPartnerId=Test;sourceCompanyCode=Test;sourceProduct=Sage300;fein=Test;ts=2015-12-15T23:37:20.901Z;ec=50;companyName=Test;address1=Test;address2=Test;city=Test;state=AK;zip=Test;";
/*{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};
*/
static const BYTE rgbIV[sizeof(rgbPlaintext)];// =
/*{
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};
*/
static const BYTE rgbAES128Key[] = "#e-rAwru7!?_acrum5g_sWeP6gEJU58\0";

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

	// Cleaning Up Routine 

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