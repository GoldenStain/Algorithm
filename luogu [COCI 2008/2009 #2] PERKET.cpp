#include <stdio.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <string>

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

int n;
std::array<int, 15> sours, bitters;
int ans = 1e9 + 1;

void recipe(int now, int sour, int bitter, int cnt) {
    if (now == n) {
        if (cnt)
            ans = std::min(ans, std::abs(sour - bitter));
        return;
    }
    recipe(now + 1, sour, bitter, cnt);
    recipe(now + 1, sour * sours[now], bitters[now] + bitter, cnt + 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
    for (int i = 0; i < n; i++) std::cin >> sours[i] >> bitters[i];
    recipe(0, 1, 0, 0);
    std::cout << ans << std::endl;
    return 0;
}