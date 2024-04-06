#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <cmath>
#include <vector>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 15, M = 1 << 11;

typedef long long LL;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int n, m;
LL f[N][M];
vector<int> Useful, Trans[M];
bool st[M];

bool check(int a, int b)
{
    if (a & b)
        return 0;
    if (!st[a | b])
        return 0;
    return 1;
}

void init()
{
    for (int i = 0; i < (1 << n); i++)
    {
        int cnt = 0;
        bool flag = true;
        for(int j = n - 1; j >= 0; j--)
        {
            if((i >> j)&1)
            {
                if(cnt&1)
                {
                    flag = false;
                    break;
                }
                cnt = 0;
            }
            else
                cnt++;
        }
        if (cnt & 1)
            flag = false;
        st[i] = flag;
    }
    for (int i = 0; i < (1 << n); i++)
    {
        Trans[i].clear();
        for(int j = 0; j < (1 << n); j++)
            if (check(i, j))
                Trans[i].push_back(j);
    }
}

LL dp()
{
    memset(f, 0, sizeof(f));
    f[1][0] = 1;
    for(int i = 2; i <= m + 1; i++)
        for(int j = 0; j < 1<<n; j++)
        {
            f[i&1][j] = 0;
            for(int k:Trans[j])
                f[i][j] += f[(i-1)][k];
        }
    return f[(m + 1)][0];
}

int main()
{
    while (1)
    {
        R(n);
        R(m);
        init();
        if (!n && !m)
            break;
        printf("%lld\n", dp());
    }
    return 0;
}
