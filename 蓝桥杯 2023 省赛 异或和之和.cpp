#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;
const int N = 1e5 + 5, M = 21;

typedef long long ll;

int n, w[M][2];
ll s[N];

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        ll x;
        scanf("%lld", &x);
        s[i] = s[i - 1] ^ x;
    }
    ll ans = 0;
    for(int i = 0; i <= n; i ++)
     for(int j = 0; j <= 20; j ++)
      w[j][(s[i] >> j) & 1] ++;
    for(int i = 0; i <= 20; i ++)
        ans += (ll) (1 << i) * w[i][0] * w[i][1];
    cout << ans << endl;
    system("pause");
    return 0;
}