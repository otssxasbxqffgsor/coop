#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "stdlib.h"
#include "UrlEn.h"
#include "stdlib.h"
#include "string.h"
#include "EncryptoCng.h"

int main(){
	char key[100];
	char *_finalUrl;
	//char  _CollectParUrl[] = "businessPartner;Id=22;sourceCompanyCode=22;sourceProduct=Sage100;fein=22;ts=2015-12-19T01:52:50.983Z;ec=50;";
	char  _CollectParUrl[] = "TestMe";// "businessPartner;Id=22;sourceCompanyCode=22;sourceProduct=Sage100;fein=22;ts=2015-12-19T01:52:50.983Z;ec=50;";

	char _testUrl[] = "0QRHBeZ4CKGpik2KnBpNlUAwZ9aL9BVUaTpKqJE/eCYTdYKw5NUVUhwiqvaZfHFkkVeQsi2Gh0Co5kqLSo4hSeS6MyOdvktn2rhhaloVd0vp5kGF18fayqJcB1FTZD/U48eqYlNx5HfBG4ilCS14XQ==";


	std::string URL_PATH_300 = "https://pgmorww11v.paigroup.corp/DDP.Web/Home/Sage100/?key=";
	////char url[] = "A/B";
	//char ToENcode[sizeof(url)];
	//strcpy(ToENcode, url);
	Encypto *EncryptClass = (Encypto*)malloc(sizeof(Encypto));
	UrlEn *EncodClass = (UrlEn*)malloc(sizeof(UrlEn));

	//char *t = EncodClass->Encode(url, sizeof(url));
	//printf("\n This is the Encoded String -> %s", t);
	//char *DeCodedStr = EncodClass->Decode(EncodedStr, sizeof(EncodedStr));
	



	// If _CollectParUrl is acrually a pointer of the array, of that is pointer to pointer then use Len
	std::string x = EncryptClass->Encrypt(_CollectParUrl, sizeof(_CollectParUrl));
	//const char* p_c_str = x.c_str();
	//const char* p_data = x.data();
	//const char* p_x0 = &x[0];
	//char* p_x0_rw = &x[0];
	
	/*int T_Int = strlen(&x[0]);*/
	_finalUrl = EncodClass->Encode(&x[0], x.length());

	URL_PATH_300.append(x);

	ShellExecute(NULL, "open", &URL_PATH_300[0],
		NULL, NULL, SW_SHOWNORMAL);

	return true;
}