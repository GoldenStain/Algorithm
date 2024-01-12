#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int n, k, upb;
int h[N], w[N];

inline int read()
{
    int x = 0;char ch = getchar();
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

bool check(int x)
{
    int res = 0;
    for(int i = 1; i <= n; i++)
        res += (h[i] / x) * (w[i] / x);
    return res >= k;
}

int main()
{
    n = read();k =read();
    for(int i = 1; i <= n; i++)
    {
        h[i] = read();w[i] = read();
        upb = max(upb, min(h[i], w[i])); 
    }
    int l = 1, r = upb;
    while(l < r)
    {
        int mid = l + r + 1>> 1;
        if(check(mid))
            l = mid;
        else r = mid - 1;
    }
    printf("%d\n", l);
    return 0;
}
