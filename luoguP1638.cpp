#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <string.h>
#include <cmath>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 1e6 + 5, M = 2e3 + 5;

int n, m;
int a[N];
int mp[M];

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

int cnt;
int ansl, ansr, anslen = N;

void solve()
{
    int i = 1;
    for (int j = 1; j <= n; j++)
    {
        if (mp[a[j]] == 0)
            cnt++;
        mp[a[j]]++;
        if (cnt == m)
        {
            while (cnt == m)
            {
                mp[a[i]] = max(0, mp[a[i]] - 1);
                if (mp[a[i]] == 0)
                    cnt--;
                i++;
            }
            i--;
            mp[a[i]]++;
            cnt++;
            if (j - i + 1 < anslen)
            {
                ansl = i;
                ansr = j;
                anslen = j - i + 1;
            }
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    For(i, 1, n)
        scanf("%d", &a[i]);
    solve();
    printf("%d %d", ansl, ansr);
    return 0;
}
