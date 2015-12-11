#include "unit_test.h"

TEST ts_timespan_test(){
	int count = 0;
	for (count = 0; count < 3; count ++)
	{
		TIMESPAN ts;
		ASSERT(ts_create_timespan(&ts) == 0);
		ASSERT(ts.end_status == END_IS_EMPTY);
		ASSERT(ts_update_end(&ts) == 0);
		ASSERT(ts.end_status == END_NOT_EMPTY);
		ASSERT(ts_get_timespan_microsecond(ts) == 0);
		ts_print_timespan(ts);
		ts_update_print_timespan(&ts);
	}

	//测试不引入其他命令的情况下，时间获取精度是否达到微妙级，结果：达到标准
	for (count = 0; count < 3; count ++)
	{
		TIMESPAN ts;
		ts_create_timespan(&ts) == 0;
		ts_update_print_timespan(&ts);
	}

	PASS();
}

TEST ts_timespan_test_for_cpu_time(){
	int count = 0;
	for (count = 0; count < 3; count ++)
	{
		TIMESPAN ts;
		ASSERT(ts_create_timespan_for_cpu_time(&ts) == 0);
		ASSERT(ts.end_status == END_IS_EMPTY);
		ASSERT(ts_update_end_for_cpu_time(&ts) == 0);
		ASSERT(ts.end_status == END_NOT_EMPTY);
		ASSERT(ts_get_timespan_microsecond(ts) == 0);
		ts_print_timespan(ts);
		ts_update_print_timespan_for_cpu_time(&ts);
	}

	//测试不引入其他命令的情况下，时间获取精度是否达到微妙级，结果：达到标准
	for (count = 0; count < 3; count ++)
	{
		TIMESPAN ts;
		ts_create_timespan_for_cpu_time(&ts) == 0;
		ts_update_print_timespan_for_cpu_time(&ts);
	}

	PASS();
}



SUITE(ts_timespan_suite) {
	RUN_TEST(ts_timespan_test);
	RUN_TEST(ts_timespan_test_for_cpu_time);
}

TEST tm_time_format_conversion_test(){
	TIME tm = tm_create_time();
	ASSERT(tm.now.year == 2015);
	ASSERT(tm.now.month == 12);
	ASSERT_STR_EQ(tm.date, "2015-12-11");
	tm_print_current_date(tm);
	tm_print_current_time(tm);
	tm_print_current_datetime(tm);
	PASS();
}



SUITE(tm_time_format_conversion_suite) {
	RUN_TEST(tm_time_format_conversion_test);
}



GREATEST_MAIN_DEFS();


void unit_test(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(ts_timespan_suite);
	RUN_SUITE(tm_time_format_conversion_suite);
	GREATEST_MAIN_END();

}


char *stringRand(uint32_t length)
{
	uint32_t count = 0;
	char *buf = NULL;
	buf  = (char *)calloc(length + 1, sizeof(char));
	struct timeval time_seed;
	gettimeofday(&time_seed, NULL);
	srand48(time_seed.tv_usec);
	for (count = 0; count < length; count ++)
	{
		uint32_t rand_num =lrand48() % 75;
		buf[count] = '0' + rand_num;
	}
	buf[count] = '\0';
	return buf;
}



