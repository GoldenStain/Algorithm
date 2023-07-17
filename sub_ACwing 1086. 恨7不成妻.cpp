#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 20, P = 1e9 + 7;

struct F
{
    ll s0, s1, s2;
} f[N][7][7];

int T, arr[N], len;
ll pw[N];

ll mod(ll x, int y)
{
    return (x % y + y) % y;
}

F calc(int now, int sum, ll num, bool limit)
{
    if (!now)
        return {sum && num, 0, 0};
    //if(f[now][sum % 7][num % 7].s0 >= 0) return f[now][sum % 7][num % 7];
    if(f[now][sum][num].s0 >= 0) return f[now][sum][num];
    int up = limit ? arr[now] : 9;
    F ans = {0, 0, 0};
    for (int i = 0; i <= up; i++)
    {
        if(i == 7) continue;
        F tmp = calc(now - 1, (sum + i) % 7, (num * pw[now] + i) % 7, limit && (up == i));
        ll oft = i * pw[now - 1] % P; //oft表示offset
        ans.s0 = mod(ans.s0 + tmp.s0, P);
        ans.s1 = mod(ans.s1 + tmp.s1 + oft * tmp.s0 % P, P);
        ans.s2 = mod(ans.s2 + oft * oft % P * tmp.s0 % P + 2 * oft * tmp.s1 % P + tmp.s2, P);
    }
    if(!limit) f[now][sum][num] = ans;
    return ans;
}

ll solve(int n)
{
    len = 0;
    if (!n)
        return 0;
    while (n)
    {
        arr[++len] = n % 10;
        n /= 10;
    }
    return calc(len, 0, 0, 1).s2;
}

int main()
{
    ll L, R;
    pw[0] = 1;
    for (int i = 1; i <= 18; i++)
    {
        pw[i] = pw[i - 1] * 10;
    }
    scanf("%d", &T);
    memset(f, -1, sizeof(f));
    while (T--)
    {
        scanf("%lld%lld", &L, &R);
        printf("%lld\n", solve(R) - solve(L - 1));
    }
    return 0;
}