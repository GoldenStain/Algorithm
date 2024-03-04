#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
typedef long long LL;

const int N = 2e5 + 5;
const double INF = -1e10;
const LL mod = 1e9 + 7;

int n, k;
LL a[N];

bool cmp(int a, int b)
{
    return abs(a) > abs(b);
}

LL get_min()
{
    LL ans = a[n];
    for (int i = n - 1; i >= n - k + 1; i--)
    {
        ans = ans * a[i] % mod;
    }
    return ans;
}

LL get_max(int b, int tar)
{
    LL ans = a[1];
    for(int i = 2; i <= k; i++)
    {
        if(i != b)
        {
            ans = ans * a[i] % mod;
        }
    }
    if(b != -1)
        ans = ans * a[tar] % mod;
    return ans;
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    sort(a + 1, a + n + 1, cmp);
    int cnt = 0, p1 = -1, p2 = -1, m1 = -1, m2 = -1;
    LL ans = 1;
    for (int i = 1; i <= k; i++)
        if (a[i] < 0)
            cnt++;
    if (cnt & 1) // 绝对值最大的k个数字只能得到负数
    {
        for (int i = k; i; i--)
        {
            if (p1 != -1 && m1 != -1)
                break;
            if (p1 == -1 && a[i] > 0)
                p1 = i;
            if (m1 == -1 && a[i] < 0)
                m1 = i;
        }
        for (int i = k + 1; i <= n; i++)
        {
            if (p2 != -1 && m2 != -1)
                break;
            if (p2 == -1 && a[i] > 0)
                p2 = i;
            if (m2 == -1 && a[i] < 0)
                m2 = i;
        }
        long double f1 = INF, f2 = INF;
        if(m1!=-1&&p2!=-1)
            f1 = (long double)a[p2]/(long double)(-a[m1]);
        if(p1!=-1&&m2!=-1)
            f2 = (long double)(-a[m2])/(long double)a[p1];
        if (f1==INF&&f2==INF) // 无法得到正数
        {
            ans = get_min();
        }
        if(f1 > f2)
            ans = get_max(m1, p2);
//-------------------------------------------------------------------------------------------------------
        else if(f1 < f2) //这里不能只写if,否则在无法得到正数的情况下，会把答案从get_min替换成这个get_max
            ans = get_max(p1, m2);
//-------------------------------------------------------------------------------------------------------
    }
    else
        ans = get_max(-1, -1);
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}