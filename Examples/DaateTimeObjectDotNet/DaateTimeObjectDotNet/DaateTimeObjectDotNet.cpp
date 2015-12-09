// DaateTimeObjectDotNet.cpp : Defines the entry point for the console application.

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "ctime"



int _tmain(int argc, _TCHAR* argv[])
{

	time_t now;
	tm *t = localtime(&now);


	return 0;
}

