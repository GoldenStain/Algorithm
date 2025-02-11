#include <stdio.h>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

#define For(i, j, n) for (int i = j; i <= n; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
    do {                                     \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
    } while (0);
#else
#define DEBUG_LOG(fmt, ...) \
    do {                    \
    } while (0);
#endif

template <typename T>
inline T read() {
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

std::vector<int> arr(101);

int binary_serach(int tar) {
    int l = 0, r = 100;
    while(l < r) {
        int mid = (l + r) >> 1;
        if (arr[mid] >= tar)
            r = mid;
        else
            l = mid + 1;
    }
    if (l == 100)
        return -114514;
    return arr[l];
}

int stl_search(int tar) {
    auto it = std::lower_bound(arr.begin(), arr.end(), tar);
    if (it == arr.end())
        return -114514;
    return *it;
}

template <typename Func>
long long measure_time(Func func, int iterations = 10000000) {
    using namespace std::chrono;
    long long total_time = 0;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        func(rand() % 100);
    }
    auto end = high_resolution_clock::now();
    total_time += duration_cast<microseconds>(end - start).count();

    return total_time;  // 返回总时间
}

int main() {
    srand(114514);
    for (int i = 0; i < 100; i++) arr[i] = rand() % 5455;
    arr[100] = -114514;
    std::sort(arr.begin(), arr.end());
    long long time1 = measure_time(&binary_serach);
    long long time2 = measure_time(&stl_search);
    std::cout << "my time: " << time1 << std::endl << "stl time: " << time2 << std::endl;
    return 0;
}
