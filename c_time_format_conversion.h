#ifndef C_TIME_FORMAT_CONVERSION
#define C_TIME_FORMAT_CONVERSION
#include <time.h>
#include <string.h>
#include <stdio.h>

#define year tm_year + 1900
#define month tm_mon + 1
#define day tm_mday
#define hour tm_hour
#define minute tm_min
#define second tm_sec

typedef struct TIME{
	struct tm now;
	char date[16];
	char time[16];
	char datetime[32];
}TIME;

TIME tm_create_time(void);
static inline void tm_print_current_date(const TIME tm)
{
	printf("%s\n", tm.date);
}

static inline void tm_print_current_time(const TIME tm)
{
	printf("%s\n", tm.time);
}

static inline void tm_print_current_datetime(const TIME tm)
{
	printf("%s\n", tm.datetime);
}

#endif // C_TIME_FORMAT_CONVERSION

