#include "stdafx.h"

// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
#include <windows.h>
#include <cstdio>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
#include "..\cryptopp560\integer.h"
using CryptoPP::Integer;

int main(){
	Integer i;
	cout<<i;

return 0;
}