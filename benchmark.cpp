#include "WoodyLogger.h"
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <cstdio>
#include <functional>
#ifdef __linux__
#include<sys/types.h>
#include<sys/sysinfo.h>
#endif

using namespace woodycxx;

inline void SetCpuAffinity(int cpu)
{
    if (cpu >= 0) {
#ifdef __linux__
        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(cpu, &mask);
        sched_setaffinity(0, sizeof(mask), &mask);
#endif
    }
}

/* Returns microseconds since epoch */
uint64_t timestamp_now()
{
    return std::chrono::high_resolution_clock::now().time_since_epoch() / std::chrono::microseconds(1);
}

void log_benchmark(int cpu)
{
    SetCpuAffinity(cpu);
    int const iterations = 1e6;
    char const * const benchmark = "benchmark";
    uint64_t begin = timestamp_now();
    for (int i = 0; i < iterations; ++i)
        LOG_INFO("Logging %s%d%c%f", benchmark, i, 'K', -42.42);
    uint64_t end = timestamp_now();
    long int avg_latency = (end - begin) * 1000 / iterations;
    printf("\tAverage WoodyLogger Latency = %ld nanoseconds\n", avg_latency);
}

template < typename Function >
void run_benchmark(Function && f, int thread_count, int total_cores)
{
    printf("Thread count: %d\n", thread_count);
    std::vector < std::thread > threads;
    for (int i = 0; i < thread_count; ++i) {
	    threads.emplace_back(f, (i % total_cores)*2 + 1);
    }
    for (int i = 0; i < thread_count; ++i) {
	    threads[i].join();
    }
}

int main()
{
    //TODO: total cpu cores need to be set
    int TOTAL_CORES = 2;
    WOODY_LOGGER_START(0); //TODO: The Logger thread CPU
    WOODY_LOGGER_INIT("/dev/null", false);
    WOODY_LOGGER_LEVEL(DEBUG);

    for (auto threads : { 1, 2, 4, 8, 16 })
    	run_benchmark(log_benchmark, threads, TOTAL_CORES/2);

    WOODY_LOGGER_STOP();
    return 0;
}

//    struct timespec timestamp_start;
//    clock_gettime(CLOCK_REALTIME, &timestamp_start);
//
//    for (int i = 0; i < 1e7; ++i)
//    {
//        LOG_ERROR("%0.10f:%04d:%+g:%s:%p:%c:%%\n",
//                  1.234, 42, 3.13, "str", (void*)1000, (int)'X');
//    }
//    struct timespec timestamp_end;
//    clock_gettime(CLOCK_REALTIME, &timestamp_end);
//    int64_t time_diff = (
//        (timestamp_end.tv_sec * 1e9 + timestamp_end.tv_nsec) -
//            (timestamp_start.tv_sec * 1e9 + timestamp_start.tv_nsec)
//    ) / 1e7;
//    printf("PrintLogThread time cost = %lld ns.\n", time_diff);

