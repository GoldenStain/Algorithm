#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 11;

int a, b, f[N][N];

void init()
{
    for (int i = 0; i <= 9; i++)
    {
        if (i == 4)
            continue;
        f[1][i] = 1;
    }
    for (int i = 2; i < N; i++)
        for (int j = 0; j <= 9; j++)
        {
            if (j == 4)
                continue;
            bool flag = j == 6;
            for (int k = 0; k <= 9; k++)
            {
                if (k == 4 || (flag & k == 2))
                    continue;
                f[i][j] += f[i - 1][k];
            }
        }
}

int num[N], len;

int solve(int x)
{
    if (!x)
        return 1;
    int res = 0;
    len = 0;
    while (x)
    {
        num[++len] = x % 10;
        x /= 10;
    }
    int last = 0;
    for (int i = len; i >= 1; i--)
    {
        for (int j = 0; j < num[i]; j++)
        {
            if (j == 4 || (last == 6 && j == 2))
                continue;
            res += f[i][j];
        }
        if (num[i] == 4 || (last == 6 && num[i] == 2))
            break;
        last = num[i];
        if (i == 1)
            res++;
    }
    return res;
}

int main()
{
    init();
    while (cin >> a >> b && a && b)
    {
        cout << solve(b) - solve(a - 1) << endl;
    }
    return 0;
}