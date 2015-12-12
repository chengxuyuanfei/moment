# moment

标签（空格分隔）： github

---

## timespan

### 精度说明
> 时间获取调用本身需要消耗20ns~1000ns的时间，不同时间源的时间也有所差别，在该模块中，能够保证时间精度达到微秒级别，即调用本身少于一微秒的时间。具体测试情况可参考[c_time_test][1]

### 使用建议
> 当使用该模块进行性能测试时，建议使用带有_for_cpu_time后缀的函数，同时，不建议使用该模块对纳秒级程序进行性能测试

### c_timespan模块API

```
//创建一个timespan结构体，并使用当前时间填充结构体
//返回0，执行成功，返回-1，执行失败
int ts_create_timespan(TIMESPAN *ts)

//记录当前时间，并填充到end
int  ts_update_end(TIMESPAN *ts)

//刷新TIMESPAN中的数值
int ts_update_timespan(TIMESPAN *ts)

//获取时间间隔，单位分别为纳秒，微秒，毫秒，秒
uint64_t ts_get_timespan_nanosecond(const TIMESPAN ts)
uint64_t ts_get_timespan_microsecond(const TIMESPAN ts)
uint64_t ts_get_timespan_millisecond(const TIMESPAN ts)
uint32_t ts_get_timespan_second(const TIMESPAN ts)

//打印时间间隔，单位分别为纳秒，微秒，毫秒，秒
void ts_print_timespan_nanosecond(const TIMESPAN ts)
void ts_print_timespan_microsecond(const TIMESPAN ts)
void ts_print_timespan_millisecond(const TIMESPAN ts)
void ts_print_timespan_second(const TIMESPAN ts)

//打印时间间隔，输出纳秒和秒
void ts_print_timespan(const TIMESPAN ts)

//记录当前时间点，并打印时间间隔
void ts_update_print_timespan(TIMESPAN *ts)



//以下三个函数用于需要获取程序的cpu时间片占用时间的时差
//默认使用类似现实时间的方式，而使用cpu时间片方式，可以知道程序真正使用的cpu时间，当程序中出现io 等sleep操作时，这类时间并不计算在内
int ts_create_timespan_for_cpu_time(TIMESPAN *ts)
int  ts_update_end_for_cpu_time(TIMESPAN *ts)
void ts_update_print_timespan_for_cpu_time(TIMESPAN *ts)

```

### 使用示例
```
TIMESPAN ts;
ts_create_timespan(&ts);
ts_update_end(&ts);
ts_print_timespan(ts);
ts_update_print_timespan(&ts);

TIMESPAN ts;
ts_create_timespan(&ts) == 0;
ts_update_print_timespan(&ts);

TIMESPAN ts;
ts_create_timespan_for_cpu_time(&ts) == 0;
ts_update_print_timespan_for_cpu_time(&ts);
```


  [1]: https://github.com/chengxuyuanfei/c_time_test
