#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long LL;

const int N = 5005;

LL s, t[N], c[N], n;
LL f[N];
bool g[N];

int main()
{
    scanf("%lld%lld", &n, &s);
    for(int i = 1; i <= n; i++)
    {
        scanf("%lld%lld", &t[i], &c[i]);
        t[i] += t[i - 1];
        c[i] += c[i - 1];
    }
    for(int i = 1; i <= n ; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if (!g[i]) f[i] = f[j] + (LL) s * (c[n]- c[j]) + (LL) t[i] * (c[i] - c[j]), g[i] = 1;
            else f[i] = min(f[i], f[j] + (LL) s * (c[n]- c[j]) + (LL) t[i] * (c[i] - c[j]));
        }
    }
    printf("%lld\n", f[n]);
    system("pause");
    return 0;
}