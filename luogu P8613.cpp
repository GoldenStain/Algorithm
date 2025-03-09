#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <array>
#include <unordered_map>

#define For(i, j, n) for(int i = j ; i <= n ; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
do {                  \
\
fprintf(stderr, fmt, ##__VA_ARGS__); \
} while (0);
#else
#define DEBUG_LOG(fmt, ...) \
do {                    \
} while (0);
#endif

template <typename T>
inline T read()
{
    T x = 0;
    int f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
    return x * f;
}

const int N = 100005;

std::array<int, N> tree{}, arr{}, backup{};
std::unordered_map<int, int> pos_table;
int n;

int lowbit(int x) {
    return x & (-x);
}

void update(int pos, int x) {
    for(int i = pos; i <= n; i += lowbit(i))
        tree[i] += x;
}

int get(int pos) {
    int ans = 0;
    for (int i = pos; i; i -= lowbit(i))
        ans += tree[i];
    return ans;
}

std::array<long long, N> cnt{};

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
    for(int i = 1; i <= n; i++)
        std::cin >> arr[i], backup[i] = arr[i];
    // 进行排序、离散化
    // 这里不能用backup.end(),因为后面都填充了0，如果右边界是back.end()，那么这些0都要跑出来了。
    std::sort(backup.begin() + 1, backup.begin() + n + 1);
    for(int i = 1; i <= n; i++)
        pos_table[backup[i]] = i;
    for (int i = 1; i <= n; i++)
        arr[i] = pos_table[arr[i]];
    
    // for (int i = 1; i <= n; i++)
    //     std::cout << arr[i] << " ";
    // std::cout << "\n";
    // exit(0);

    for (int i = 1; i <= n; i++) {
        cnt[i] = i - 1 - get(arr[i]);
        update(arr[i], 1);
    }
    tree.fill(0);
    for (int i = n; i >= 1; i--) {
        cnt[i] += get(arr[i] - 1);
        update(arr[i], 1);
    }
    long long ans = 0;
    for (int i = 1; i <= n; i++)
        ans += cnt[i] * (cnt[i]+1) / 2;
    std::cout << ans << std::endl;
    return 0;
}
