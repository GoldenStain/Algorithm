#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

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

const int N = 5e6 + 5;

int n, a[N];

int main()
{
    cin >> n;
    a[1] = 1;
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (!a[i])
            continue;
        cnt++;
        for (int j = i; j <= n; j += i)
            a[j] ^= 1;
    }
    cout << cnt << endl;
    return 0;
}
