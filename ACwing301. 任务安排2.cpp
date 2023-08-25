#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 3e5 + 5;

int n, hh, tt, q[N];
LL f[N], t[N], c[N], s;

int main()
{
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &t[i], &c[i]);
        t[i] += t[i - 1];
        c[i] += c[i - 1];
    }
    for (int i = 1; i <= n; i++)
    {
        while (hh < tt && (f[q[hh + 1]] - f[q[hh]]) <= (c[q[hh + 1]] - c[q[hh]]) * (s + t[i]))
            hh++;
        f[i] = f[q[hh]] + s * (c[n] - c[q[hh]]) + t[i] * (c[i] - c[q[hh]]);
        while (hh < tt && (f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt]]) > (c[q[tt]] - c[q[tt - 1]]) * (f[i] - f[q[tt]]))
            tt--;
        q[++tt] = i;
    }
    printf("%lld\n", f[n]);
    system("pause");
    return 0;
}