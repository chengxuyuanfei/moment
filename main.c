#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "unit_test.h"

int main(void)
{
	unit_test(0, NULL);

	return 0;
}

//测试使用CLOCK_PROCESS_CPUTIME_ID时钟源时，获取时间指令本身的耗时。
void clock_gettime_by_process_cpu_time(void)
{
	clockid_t clock = CLOCK_PROCESS_CPUTIME_ID;
	struct timespec res[10000] = {0};
	int count = 0;
	for (count = 0 ; count < 10000; count ++)
	{
		clock_gettime(clock, &res[count]);
	}
	long long sum = 0;
	for (count = 0; count < 9999; count ++)
	{
		sum += res[count+ 1].tv_nsec - res[count].tv_nsec;
		printf("差:%ldns\t", res[count+ 1].tv_nsec - res[count].tv_nsec);
	}
	printf("\n平均用时:%lfns\n", (sum / (double)9999));
}
//测试使用CLOCK_THREAD_CPUTIME_ID时钟源时，获取时间指令本身的耗时。
void clock_gettime_by_thread_cpu_time(void)
{
	clockid_t clock = CLOCK_THREAD_CPUTIME_ID;
	struct timespec res[10000] = {0};
	int count = 0;
	for (count = 0 ; count < 10000; count ++)
	{
		clock_gettime(clock, &res[count]);
	}
	long long sum = 0;
	for (count = 0; count < 9999; count ++)
	{
		sum += res[count+ 1].tv_nsec - res[count].tv_nsec;
		printf("差:%ldns\t", res[count+ 1].tv_nsec - res[count].tv_nsec);
	}
	printf("\n平均用时:%lfns\n", (sum / (double)9999));
}
//测试使用CLOCK_REALTIME时钟源时，获取时间指令本身的耗时。
void clock_gettime_by_clock_real_time(void)
{
	clockid_t clock = CLOCK_REALTIME;
	struct timespec res[10000] = {0};
	int count = 0;
	for (count = 0 ; count < 10000; count ++)
	{
		clock_gettime(clock, &res[count]);
	}
	long long sum = 0;
	for (count = 0; count < 9999; count ++)
	{
		sum += res[count+ 1].tv_nsec - res[count].tv_nsec;
		printf("差:%ldns\t", res[count+ 1].tv_nsec - res[count].tv_nsec);
	}
	printf("\n平均用时:%lfns\n", (sum / (double)9999));
}
//测试使用CLOCK_MONOTONIC时钟源时，获取时间指令本身的耗时。
void clock_gettime_by_clock_monotonic(void)
{
	clockid_t clock = CLOCK_MONOTONIC;
	struct timespec res[10000] = {0};
	int count = 0;
	for (count = 0 ; count < 10000; count ++)
	{
		clock_gettime(clock, &res[count]);
	}
	long long sum = 0;
	for (count = 0; count < 9999; count ++)
	{
		sum += res[count+ 1].tv_nsec - res[count].tv_nsec;
		printf("差:%ldns\t", res[count+ 1].tv_nsec - res[count].tv_nsec);
	}
	printf("\n平均用时:%lfns\n", (sum / (double)9999));
}
//测试使用CLOCK_MONOTONIC_RAW时钟源时，获取时间指令本身的耗时。
void clock_gettime_by_clock_monotonic_raw(void)
{
	clockid_t clock = CLOCK_MONOTONIC_RAW;
	struct timespec res[10000] = {0};
	int count = 0;
	for (count = 0 ; count < 10000; count ++)
	{
		clock_gettime(clock, &res[count]);
	}
	long long sum = 0;
	for (count = 0; count < 9999; count ++)
	{
		sum += res[count+ 1].tv_nsec - res[count].tv_nsec;
		printf("差:%ldns\t", res[count+ 1].tv_nsec - res[count].tv_nsec);
	}
	printf("\n平均用时:%lfns\n", (sum / (double)9999));
}
//测试使用gettimeofday时，获取时间指令本身的耗时。
void clock_gettime_by_gettimeofday(void)
{
	struct timeval res[100] = {0};
	int count = 0;
	for (count = 0; count < 100; count ++)
	{

		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC, &start);
		gettimeofday(&res[count], NULL);
		clock_gettime(CLOCK_MONOTONIC, &end);
		printf("gettimeofday:sec:%ld\t\tnsec:%ld\n",  end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
	}
	long long sum = 0;
	for (count = 0; count < 99; count ++)
	{
		sum += res[count+ 1].tv_usec - res[count].tv_usec;
		printf("差:%ldms\t", res[count+ 1].tv_usec - res[count].tv_usec);
	}
	printf("\n平均用时:%lfms\n", (sum / (double)99));
}
//测试使用usleep时，获取指令本身的非阻塞耗时。
void usleep_test(void)
{
	clockid_t clock = CLOCK_REALTIME;
	struct timespec start, end;
	int count = 0;
	for (count = 0; count < 100; count ++)
	{
		clock_gettime(clock, &start);
		usleep(20000);
		clock_gettime(clock, &end);
		printf("usleep sec:%ld\t", end.tv_sec - start.tv_sec);
		printf("ns:%ld\n", end.tv_nsec - start.tv_nsec);
	}
}
//测试使用clock_nanosleep时，获取指令本身的非阻塞耗时。
void clock_nanosleep_test(void)
{
	struct timespec res;
	res.tv_nsec = 10000000;
	res.tv_sec = 0;
	clockid_t clock = CLOCK_REALTIME;
	struct timespec start, end;
	int count = 0;
	for (count = 0; count < 100; count ++)
	{
		clock_gettime(clock, &start);
		clock_nanosleep(clock, 0, &res, NULL);
		clock_gettime(clock, &end);
		printf("nanosleep sec:%ld\t", end.tv_sec - start.tv_sec);
		printf("ns:%ld\n", end.tv_nsec - start.tv_nsec);
	}
}

//测试使用CLOCK_PROCESS_CPUTIME_ID时钟源时，获取到的时间是否会包括sleep的时间。（测试结果：不会）
void clock_gettime_by_process_cpu_time_with_sleep(void)
{
	clockid_t clock = CLOCK_PROCESS_CPUTIME_ID;
	struct timespec res[2] = {0};
	int count = 0;
	clock_gettime(clock, &res[count]);
	printf("sec:%ld\tnsec:%ld\n", res[count].tv_sec, res[count].tv_nsec);
	for (count = 0 ; count < 2; count ++)
	{
		sleep(3);
		clock_gettime(clock, &res[count]);
		printf("sec:%ld\tnsec:%ld\n", res[count].tv_sec, res[count].tv_nsec);
	}
	long long sum = 0;
	for (count = 0; count < 1; count ++)
	{
		sum += res[count+ 1].tv_nsec - res[count].tv_nsec;
		printf("差:%ldns\n", res[count+ 1].tv_nsec - res[count].tv_nsec);
	}
}
