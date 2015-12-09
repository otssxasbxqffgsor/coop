#include <iostream>
#include <ctime>

int time()
{
	// current date/time based on current system
	time_t now = time(0);


	tm *lt = localtime(&now);
	char dateObject[25];

	sprintf_s(dateObject, sizeof(dateObject), "%d-%d-%dT%d:%d:%d.%dZ", (1900 + lt->tm_year), lt->tm_mon, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec);
	printf(dateObject);

	return true;
}
