#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "UrlEn.h"
#include "stdlib.h"
#include "string.h"

int main(){
	char url[] = "0QRHBeZ4CKGpik2KnBpNlUAwZ9aL9BVUaTpKqJE/eCYTdYKw5NUVUhwiqvaZfHFkkVeQsi2Gh0Co5kqLSo4hSeS6MyOdvktn2rhhaloVd0vp5kGF18fayqJcB1FTZD/U48eqYlNx5HfBG4ilCS14XQ==";
	char ToENcode[sizeof(url)];
	strcpy(ToENcode, url);
	UrlEn *EncodClass = (UrlEn*)malloc(sizeof(UrlEn));

	char *EncodedStr = (char *)EncodClass->Encode(ToENcode, sizeof(ToENcode));
	printf("\n This is the Encoded String -> %s", EncodedStr);
	char *DeCodedStr = EncodClass->Decode(EncodedStr, sizeof(ToENcode));
	
	return true;
}