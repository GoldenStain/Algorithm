#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 1e5 + 5;

int lowbit(int x)
{
    return x & (-x);
}

int n, a[N], tr[N], h[N];

void modify(int k, int x)
{
    for (int i = k; i <= n; i += lowbit(i))
        tr[i] += x;
}

int query(int k)
{
    int res = 0;
    for (int i = k; i; i -= lowbit(i))
        res += tr[i];
    return res;
}

void init()
{
    scanf("%d", &n);
    for (int i = 2; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= n; i++)
        modify(i, 1);
}

void solve()
{
    int p, s, sum;
    int base = log2(n);
    for (int i = n; i; i--)
    {
        p = 0;
        sum = 0;
        for(s = base; s >= 0; s--)
            if(p + (1 << s) <= n && sum + tr[p + (1 << s)] < a[i] + 1)
            {   
                p += 1 << s;
                sum += tr[p];
            }
        h[i] = p + 1;
        modify(h[i], -1);
    }
}

int main()
{
    init();
    solve();
    for (int i = 1; i <= n; i++)
        printf("%d\n", h[i]);
    return 0;
}
