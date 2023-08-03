#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int N = 5e4 + 5;

int n, t, a[N], q[N], hh, tt, f[N];

bool check(int x)
{
    int res = 1e9;
    hh = tt = 0;
    q[0] = 0;
    for(int i = 1; i <= n; i++)
    {
        if(q[hh] < i - x - 1) hh++;
        f[i] = f[q[hh]] + a[i];
        while(hh <= tt && f[q[tt]] >= f[i]) tt--;
        q[++tt] = i;
    }
    for(int i = n; i >= n - x; i--)
        res = min(res, f[i]);
    return res <= t;
}

int main()
{
    scanf("%d%d", &n, &t);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    int l = 0, r = n;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid; 
        else l = mid + 1;
    }
    printf("%d", l);
    return 0;
}