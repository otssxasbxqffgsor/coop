#include "stdio.h"
#include "UrlEn.h"

int main(){

	char *ToENcode = "01234/56789";
	UrlEn *EncodClass = (UrlEn*)malloc(sizeof(UrlEn));
	char *EnCodedResults = EncodClass->Encode(ToENcode);
	
	return true;
}