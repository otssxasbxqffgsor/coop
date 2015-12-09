#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>



int main()
{

	__time64_t ltime;
	_time64(&ltime);
	
	// Refference @ https://msdn.microsoft.com/en-us/library/78zb0ese.aspx AND http://www.codeproject.com/Articles/3049/Date-and-Time-in-C
	// current date/time based on current system
	time_t *now = new time_t();
	tm *lt = new tm;
	gmtime_s(lt, &ltime);

	// Local function takes the local time based on the machine time. Forexample this function in gmt gets 22:00:00 but at the same time in vancouver it will return 14:00:00 -8 hourse
	time_t nowLocal = time(0);
	tm *lt_local = localtime (&nowLocal);
	//gmtime_s(lt_local, &nowLocal);


	char dateObject[35];
	char dateObjectLocal[35];
	
	sprintf_s(dateObject, sizeof(dateObject), "%d-%d-%dT%d:%d:%d.%dZ", (1900 + lt->tm_year), lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec, lt->tm_sec*10);
	printf(dateObject);
	printf("\n");
	sprintf_s(dateObject, sizeof(dateObject), "%d-%d-%dT%d:%d:%d.%dZ", (1900 + lt->tm_year), lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec, lt->tm_sec * 10);
	printf(dateObjectLocal);


	

	return true;
}
