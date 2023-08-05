#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;

int n, k, a[N], hh, tt, q[N];
ll res = 1e14 + 5, sum, f[N];

int main()
{
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; i++) scanf("%d", &a[i]),sum += a[i]; 
    k++;
    for(int i = 1; i <= n; i++)
    {
        if(q[hh] < i - k) hh++;
        f[i] = f[q[hh]] + a[i];
        while(hh <= tt && f[q[tt]] >= f[i]) tt--;
        q[++tt] = i;
    }
    for(int i = n; i >= n - k + 1; i--) res = min(res, f[i]);
    printf("%lld\n", sum - res);
    return 0;
}