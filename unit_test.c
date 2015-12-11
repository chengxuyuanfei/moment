#include "unit_test.h"

TEST ts_timespan_test(){
	int count = 0;
	for (count = 0; count < 1000; count ++)
	{
		TIMESPAN ts;
		if (ts_create_timespan(&ts) == -1)
			printf("create timespan error\n");
		ts_update_end(&ts);
		ASSERT(ts_get_timespan_microsecond(&ts) == 0);
	}

	ASSERT(1);
	ASSERT_STR_EQ("helloworld", "helloworld");
	PASS();
}



SUITE(ts_timespan_suite) {
	RUN_TEST(ts_timespan_test);
}


GREATEST_MAIN_DEFS();


void unit_test(int argc, char **argv)
{
	GREATEST_MAIN_BEGIN();

	RUN_SUITE(ts_timespan_suite);
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



