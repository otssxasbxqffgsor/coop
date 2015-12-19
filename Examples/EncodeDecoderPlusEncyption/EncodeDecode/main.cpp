#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "UrlEn.h"
#include "stdlib.h"
#include "string.h"
#include "EncryptoCng.h"

int main(){
	char url[] = "0QRHBeZ4CKGpik2KnBpNlUAwZ9aL9BVUaTpKqJE/eCYTdYKw5NUVUhwiqvaZfHFkkVeQsi2Gh0Co5kqLSo4hSeS6MyOdvktn2rhhaloVd0vp5kGF18fayqJcB1FTZD/U48eqYlNx5HfBG4ilCS14XQ==";
	////char url[] = "A/B";
	//char ToENcode[sizeof(url)];
	//strcpy(ToENcode, url);
	UrlEn *EncodClass = (UrlEn*)malloc(sizeof(UrlEn));

	char *t = EncodClass->Encode(url, sizeof(url));
	printf("\n This is the Encoded String -> %s", t);
	//char *DeCodedStr = EncodClass->Decode(EncodedStr, sizeof(EncodedStr));
	
	return true;
}