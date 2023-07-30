#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int N = 2e5 + 5;

int n, m, hh, tt, q[N], a[N], f[N];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i++)
    {
        if(q[hh] < i - m) hh++;
        f[i] = f[q[hh]] + a[i];
        while(hh <= tt && f[q[tt]] >= f[i]) tt--;
        
        q[++tt] = i;
    }
    int res = 1e9;
    for(int i = n; i >= n - m + 1; i--)
     res = min(res, f[i]);
    printf("%d", res);
    return 0;
}