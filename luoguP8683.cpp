#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

typedef long long LL;

const int N = 2e5 + 5;

LL ans;
int a[N],n, m;

int main()
{
    scanf("%d%d", &n, &m);
    n = n + m + 1;
    For(i, 1, n)
    {
        scanf("%d", &a[i]);
    }
    if(!m)
        For(i, 1, n)
            ans += a[i];
    else
    {
        sort(a + 1, a + n + 1);
        ans += a[n] - a[1];
        for(int i = 2; i < n; i++)
            ans += abs(a[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
