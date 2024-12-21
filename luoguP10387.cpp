#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <set>
#include <string>
#define For(i, j, n) for (int i = j; i <= n; ++i)

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
