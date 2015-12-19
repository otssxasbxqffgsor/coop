#define _CRT_SECURE_NO_WARNINGS

#include "UrlEn.h"
#include "stdlib.h"





char *UrlEn::Encode(char *_strInput, int lenStr){
	
	char *_prtStr = _strInput;
	// New Buffer
	//char _buffEncStr[3 * sizeof(_strInput)];
	char *_buffEncStr= (char*)(malloc(3 * sizeof(_strInput)));
	char *_ptrToBuffer = _buffEncStr;
	int  l = lenStr-1;
	while (l>0)
	{
		/*printf("%c",*_prtStr);*/
		l--;
		//All input characters that are not a-z, A-Z, 0-9, '-', '.', '_' or '~' are converted to their "URL escaped" version (%NN where NN is a two-digit hexadecimal number).
		if (((int)(char*)_prtStr >= 97 && (int)*_prtStr <= 122) || ((int)*_prtStr >= 0 && (int)*_prtStr <= 9) || ((int)*_prtStr >= 65 && (int)*_prtStr <= 90) || ((int)*_prtStr == 45) || ((int)*_prtStr == 46) || ((int)*_prtStr == 95) || ((int)*_prtStr == 126))
		{ 
			//strcpy ((char*)_buffEncStr++,(char*)_prtStr++);
			*_buffEncStr++ = *_prtStr++;
		}
		else
		{
			if (!*_prtStr == '\0'){
				//	// convert the value to Hex
				//unsigned char hexVal[3] = [0x01, 0x02, 0x00]
				//hexVal = _prtStr;
				char charVal[3];
				//	int HexLoc = (int)*_prtStr;
				sprintf(charVal, "%x", *_prtStr);
				//	// add % in place of the char
				//	// Shirt four bits
				//	// Add the Hex in the place of %NN
				*_buffEncStr++ = '%';
				*_buffEncStr++ = charVal[0];
				*_buffEncStr = charVal[1];

				//	*_prtStr >>= 4*sizeof(char);
				////	_prtStr++;
				////	*_prtStr = charVal[0];
				//	printf("\n%s", _strInput);
				//
				//	//_prtStr = _prtStr+sizeof(int);
				//	//*_prtStr = charVal[1];
				_buffEncStr++;
				_prtStr++;
			}
			//if (l>0)
			//*_buffEncStr = '\0'; // Add the NULL terminator to the end of the string so in print it actually is a null terminate
		}
	}
	printf("%s", _ptrToBuffer);

	return _ptrToBuffer;
};

char *UrlEn::Decode(char *_strInput, int lenStr){
	return "Decoded";
};