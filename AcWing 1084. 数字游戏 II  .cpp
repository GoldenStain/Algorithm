#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <string.h>
using namespace std;

const int N = 15, M = 105;
int a, b, n;
int f[N][10][M];
int num[N], len;

int mod(int x)
{
    return (x % n + n) % n;
}

void init()
{
    memset(f, 0, sizeof(f));
    for (int i = 0; i <= 9; i++)
        f[1][i][i % n] = 1;
    for (int i = 2; i < N; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k < n; k++)
                for (int t = 0; t <= 9; t++)
                    f[i][j][k] += f[i - 1][t][mod(k - j)];
}

int solve(int x)
{
    memset(num, 0, sizeof(num));
    if(!x) return 1;
    int res = 0;
    len = 0;
    while (x)
    {
        num[++len] = x % 10;
        x /= 10;
    }
    int last = 0;
    for (int i = len; i; i--)
    {
        int t = num[i];
        for (int j = 0; j < t; j++)
            res += f[i][j][mod(-last)];
        last += t;
        if (i == 1)
            if (last % n == 0)
                res++;
    }
    return res;
}
int main()
{
    while(cin >> a >> b >> n)
    {
        init();
        cout << solve(b) - solve(a - 1) << endl;
    }
    return 0;
}