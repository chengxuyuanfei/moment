#ifndef C_TIME
#define C_TIME
//该模块指在为性能测试等提供较高精度的时间获取，由于调用本身会花费一定的cpu时间， 且该时间几乎时随即的，故而难以达到纳秒级别。
//目前模块耗时保持在微妙级别。


#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#include <time.h>

#define END_IS_EMPTY		0
#define END_NOT_EMPTY	1

typedef struct TIMESPAN{
	struct timespec begin;
	struct timespec end;
	uint8_t end_status;
	uint64_t timespan_nanosecond;
	uint64_t timespan_microsecond;
	uint64_t timespan_millisecond;
	uint32_t timespan_second;
}TIMESPAN;

static inline int ts_create_timespan(TIMESPAN *ts)
{
	memset(ts, 0, sizeof(TIMESPAN));
	if (clock_gettime(CLOCK_MONOTONIC, &ts->begin) == -1)  return -1;
	ts->end_status = END_IS_EMPTY;
	return 0;
}

static inline int ts_update_timespan(TIMESPAN *ts)
{
	ts->timespan_nanosecond = ts->end.tv_nsec - ts->begin.tv_nsec + (ts->end.tv_sec - ts->begin.tv_sec) * 1000000000;
	ts->timespan_microsecond = (uint64_t)(ts->timespan_nanosecond / 1000);
	ts->timespan_millisecond = (uint64_t)(ts->timespan_nanosecond / 1000000);
	ts->timespan_second =  ts->end.tv_sec - ts->begin.tv_sec;
	return 0;
}

static inline int  ts_update_end(TIMESPAN *ts)
{
	if (ts->end_status == END_IS_EMPTY)
		if (clock_gettime(CLOCK_MONOTONIC, &ts->end) == -1) return -1;
		else {ts->end_status = END_NOT_EMPTY; return 0;}
	ts->begin = ts->end;
	if (clock_gettime(CLOCK_MONOTONIC, &ts->end) == -1) return -1;
	if (ts_update_timespan(ts) == -1) return -1;
	return 0;
}


static inline uint64_t ts_get_timespan_nanosecond(const TIMESPAN ts)
{
	return ts.timespan_nanosecond;
}

static inline uint64_t ts_get_timespan_microsecond(const TIMESPAN ts)
{
	return ts.timespan_microsecond;
}

static inline uint64_t ts_get_timespan_millisecond(const TIMESPAN ts)
{
	return ts.timespan_millisecond;
}

static inline uint32_t ts_get_timespan_second(const TIMESPAN ts)
{
	return ts.timespan_second;
}

static inline void ts_print_timespan_nanosecond(const TIMESPAN ts)
{
	printf("timespan:\t%ldns\n", ts.timespan_nanosecond);
}

static inline void ts_print_timespan_microsecond(const TIMESPAN ts)
{
	printf("timespan:\t%ldµs\n", ts.timespan_microsecond);
}

static inline void ts_print_timespan_millisecond(const TIMESPAN ts)
{
	printf("timespan:\t%ldms\n", ts.timespan_millisecond);
}

static inline void ts_print_timespan_second(const TIMESPAN ts)
{
	printf("timespan:\t%lds\n", ts.timespan_second);
}

static inline void ts_print_timespan(const TIMESPAN ts)
{
	printf("timespan:\t%ds %ldµs\n", ts.timespan_second, ts.timespan_microsecond);
}

static inline void ts_update_print_timespan(TIMESPAN *ts)
{
	if (ts_update_end(ts) == -1) return;
	if (ts_update_timespan(ts) == -1) return;
	ts_print_timespan(*ts);
}


//以下三个函数用于需要获取程序的cpu时间片占用时间的时差
//默认使用类似现实时间的方式，而使用cpu时间片方式，可以知道程序真正使用的cpu时间，当程序中出现io 等sleep操作时，这类时间并不计算在内
static inline int ts_create_timespan_for_cpu_time(TIMESPAN *ts)
{
	memset(ts, 0, sizeof(TIMESPAN));
	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts->begin) == -1)  return -1;
	ts->end_status = END_IS_EMPTY;
	return 0;
}


static inline int  ts_update_end_for_cpu_time(TIMESPAN *ts)
{
	if (ts->end_status == END_IS_EMPTY)
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts->end) == -1) return -1;
		else {ts->end_status = END_NOT_EMPTY; return 0;}
	ts->begin = ts->end;
	if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts->end) == -1) return -1;
	if (ts_update_timespan(ts) == -1) return -1;
	return 0;
}

static inline void ts_update_print_timespan_for_cpu_time(TIMESPAN *ts)
{
	if (ts_update_end_for_cpu_time(ts) == -1) return;
	if (ts_update_timespan(ts) == -1) return;
	ts_print_timespan(*ts);
}






#endif // C_TIME

