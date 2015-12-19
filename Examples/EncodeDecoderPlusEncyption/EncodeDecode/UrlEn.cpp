#define _CRT_SECURE_NO_WARNINGS

#include "UrlEn.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"




char *UrlEn::Encode(char *_strInput, int lenStr){
	
	char *_prtStr = _strInput;
	// New Buffer
	//char _buffEncStr[3 * lenStr];
	char _ptrToBuffer[500]; //= (char*)(malloc((3 * lenStr)*sizeof(char)));
	char * _buffEncStr = _ptrToBuffer;
	int  l = lenStr-1;
	while (l>=0)
	{

		



		/*printf("%c",*_prtStr);*/
		l--;
		//All input characters that are not a-z, A-Z, 0-9, '-', '.', '_' or '~' are converted to their "URL escaped" version (%NN where NN is a two-digit hexadecimal number).
		if (((int)*_prtStr >= 97 && (int)*_prtStr <= 122) || ((int)*_prtStr >= 48 && (int)*_prtStr <= 57) || ((int)*_prtStr >= 65 && (int)*_prtStr <= 90) || ((int)*_prtStr == 45) || ((int)*_prtStr == 46) || ((int)*_prtStr == 95) || ((int)*_prtStr == 126))
		{ 
			printf("%c\n", *_buffEncStr);
			//printf("%s", _ptrToBuffer);
			//strcpy ((char*)_buffEncStr++,(char*)_prtStr++);
			*_buffEncStr++ = *_prtStr++;
			
		}
		else
		{
			if (!*_prtStr == '\0' && ((int)*_prtStr >= 58 && (int)*_prtStr <= 64) || ((int)*_prtStr >= 91 && (int)*_prtStr <= 96) || ((int)*_prtStr >= 32 && (int)*_prtStr <= 47)){
				
				// convert the value to Hex
				//unsigned char hexVal[3] = [0x01, 0x02, 0x00]
				//hexVal = _prtStr;
				
				char charVal[3];
				sprintf(charVal, "%x", *_prtStr);
				*_buffEncStr++= '%';
				strcpy((char*)_buffEncStr++, (char*)charVal);
				strcpy((char*)_buffEncStr, (char*)charVal+1);

/*
				*_buffEncStr++ = '%';
				*_buffEncStr++ = charVal[0];
				*_buffEncStr = charVal[1];
*/
				_buffEncStr++;
				_prtStr++;
			}
		//	if (l>0)
			//*_buffEncStr = '\0'; // Add the NULL terminator to the end of the string so in print it actually is a null terminate
		}
		
			
		//return _strInput;
	}
	//printf("%s", _ptrToBuffer);
	//char t[] = "s";
	return _ptrToBuffer;
//	return NULL;
};

char *UrlEn::Decode(char *_strInput, int lenStr){
	return "Decoded";
};