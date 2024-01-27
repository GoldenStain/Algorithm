#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <math.h>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 5e5 + 5;

int n;
long double ans, a[N], s, avg;

int find(long double a[], long double x) // a[]中小于x的最大的数字的下标
{
    int l = 0, r = n;
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (a[mid] < x)
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> s;
    avg = s/(n * 1.0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    long double t;
    for(int i = 1, j = n; i <= n; i++, j--)
    {
        t = min(a[i], s/(j * 1.0));
        s -= t;
        ans += (t - avg) * (t - avg);
    }
    ans = sqrt(ans / (n*1.0));
    printf("%.4Lf", ans);
    return 0;
}