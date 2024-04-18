#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9') 
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const LL P = 998244353;

int n;

LL quick_pow(LL a, LL k)
{
    LL res = 1;
    while(k)
    {
        if(k&1) res = res*a%P;
        a = a * a % P;
        k>>=1;
    }
    return res;
}

int main()
{
    n = read();
    LL k1 = 1, k2 = 0, k3 = 0;
    for(int i = 1; i <= n; i++)
    {
        int a = read(), b = read();
        LL p_fall = 1ll*a*quick_pow(1ll*b, P-2) % P;
        LL p_up = 1ll*(b-a)*quick_pow(1ll*b, P-2) % P;
        k3 = (k3 + k1) % P;
        k2 = (k2 + p_fall * k1 % P) % P;
        k1 = (k1 * p_up) % P;
    }
    LL t = quick_pow(1ll-k2, P-2);
    t=(t%P+P)%P;
    printf("%lld",k3*t%P);
    return 0;
}