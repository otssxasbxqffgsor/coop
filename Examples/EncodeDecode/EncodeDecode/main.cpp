#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "UrlEn.h"
#include "stdlib.h"
#include "string.h"

int main(){

	char ToENcode[16] ;
	strcpy(ToENcode, "A/BCDEF");
	UrlEn *EncodClass = (UrlEn*)malloc(sizeof(UrlEn));

	char *EncodedStr = (char *)EncodClass->Encode(ToENcode, sizeof(ToENcode));
	printf("\n This is the Encoded String -> %s", EncodedStr);
	char *DeCodedStr = EncodClass->Decode(EncodedStr, sizeof(ToENcode));
	
	return true;
}