#include "c_time_format_conversion.h"

TIME tm_create_time(void)
{
	TIME tm;
	memset(&tm, 0, sizeof(tm));
	time_t tm_now;
	time(&tm_now);
	memcpy(&tm.now, localtime(&tm_now), sizeof(struct tm));
	sprintf(tm.date, "%d-%d-%d", tm.now.year, tm.now.month, tm.now.day);
	sprintf(tm.time, "%d:%d:%d", tm.now.hour, tm.now.minute, tm.now.second);
	sprintf(tm.datetime, "%d-%d-%d %d:%d:%d", tm.now.year, tm.now.month, tm.now.day, tm.now.hour, tm.now.minute, tm.now.second);
	return tm;
}


