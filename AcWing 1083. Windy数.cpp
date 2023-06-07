#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;

const int N = 15;

int a, b, num[N], len, f[N][N];

void init()
{
    for (int i = 0; i <= 9; i++)
        f[1][i] = 1;
    for (int i = 2; i < N; i++)
        for (int j = 0; j <= 9; j++)
            for (int k = 0; k <= 9; k++)
                if (abs(k - j) >= 2)
                    f[i][j] += f[i - 1][k];
}

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
    int last = -2;
    for (int i = len; i > 0; i--)
    {
        for (int j = i == len; j <= num[i] - 1; j++)
            if (abs(last - j) >= 2)
                res += f[i][j];
        if (abs(last - num[i]) >= 2)
            last = num[i];
        else
            break;
        if (i == 1)
            res++;
    }
    for (int i = len - 1; i > 0; i--)
        for (int j = i != 1; j <= 9; j++)
            res += f[i][j];
    return res;
}

int main()
{
    init();
    cin >> a >> b;
    printf("%d\n", solve(b) - solve(a - 1));
    system("pause");
    return 0;
}