#include <stdio.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

const int N = 3e5+5;

inline int read()
{
    int x = 0; char ch = getchar();
    int f = 1;
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

int n, a[N], t;
ll s[N];

int main()
{
    t = read();
    while(t -- )
    {
        ll maxs = 0, maxd = 0, ans = 0;
        int pos = 0;
        n = read();
        s[0] = a[0] = 0;
        for(int i = 1; i <= n; i ++)
        {
            a[i] = read();
            s[i] = s[i - 1] + a[i];
        }
        for(int i = 1; i <= n; i ++)
        {
            if(maxd < maxs - s[i])
            {
                maxd = maxs - s[i];
                ans = maxs;
            }
            if(s[i] > maxs)
            {
                maxs = s[i];
                pos = i;
            }
        }
        printf("%lld\n", ans);
    }
    system("pause");
    return 0;
}