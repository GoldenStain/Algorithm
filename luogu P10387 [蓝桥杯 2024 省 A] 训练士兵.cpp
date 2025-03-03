// 正解
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>

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

constexpr int N = 1e5 + 5, CAP = 1e6 + 5;

int n;

long long alone_price[CAP], S, alone_cost, total_cost;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> S;
    int pi, ci, max_ci = -1;
    for(int i = 0; i < n; i++) {
        std::cin >> pi >> ci;
        long long tmp = (long long)(pi) * ci;
        alone_price[ci] += pi;
        alone_cost += pi;
        total_cost += tmp;
        max_ci = std::max(max_ci, ci);
    }
    long long group_cost = 0;
    for(int i = 1; i <= max_ci; i++) {
        if (alone_cost < S) {
            break;
        }
        group_cost += S;
        total_cost -= alone_cost;
        alone_cost -= alone_price[i];
    }
    std::cout << group_cost + total_cost;
    return 0;
}

// my solution
typedef long long LL;

constexpr int N = 1e5 + 5;

struct Soldier {
    int p, c;
    Soldier(int p, int c) : p(p), c(c) {}
	Soldier() : p(0), c(0) {}
    bool operator<(const Soldier& other) const { return c < other.c; }
} soldiers[N];

int n;
LL S, sumofP[N], sumofPC[N];

std::set<int> setofC;

int find(int x) {
	int l = 1, r = n;
	while(l < r) {
		int mid = l + r >> 1;
		if(soldiers[mid].c < x)
			l = mid + 1;
		else 
			r = mid;
	}
	return l;
} // 第一个大于等于x的值的位置

LL sumFromVal(int val) {
	int pos = find(val);
	return (sumofPC[n] - sumofPC[pos - 1]) - (LL)val * (sumofP[n] - sumofP[pos - 1]);
}

int main() {
    n = read<int>();
    S = read<LL>();
    for (register int i = 1; i <= n; i++) {
        int p = read<int>(), c = read<int>();
        soldiers[i] = Soldier(p, c);
        setofC.insert(c);
    }
    std::sort(soldiers + 1, soldiers + n + 1);
    for (int i = 1; i <= n; i++) {
        sumofP[i] = sumofP[i - 1] + (LL)soldiers[i].p;
		sumofPC[i] = sumofPC[i - 1] + (LL)soldiers[i].c * (LL)soldiers[i].p;
    }
    LL ans = 1000000000000000000LL;
    for (auto val : setofC) {
		LL tmpAns = S * val + sumFromVal(val);
		ans = std::min(ans, tmpAns);
    }
	printf("%lld\n", ans);
    return 0;
}
