#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 10005;

short n;

inline short read()
{
    short x = 0;
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

short a[N][N];

short mx, my;

void insert(short x1, short y1, short x2, short y2)
{
    /*a[x1][y1]++;
    a[x1][y2 + 1]--;
    a[x2 + 1][y1]--;
    a[x2 + 1][y2 + 1]++;*/
    ++a[x1][y1];
    --a[x1][y2];
    --a[x2][y1];
    ++a[x2][y2];
}

int main()
{
    n = read();
    for (short i = 1; i <= n; i++)
    {
        short x1 = read() + 1, y1 = read() + 1, x2 = read() + 1, y2 = read() + 1;
        mx = max(mx, x2);
        my = max(my, y2);
        insert(x1, y1, x2, y2); // 矩阵差分
    }
    int ans = 0;
    for (short i = 1; i <= mx; i++)
        for (short j = 1; j <= my; j++)
        {
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
            if (a[i][j] >= 1)
                ans++; // 以每个格子为单元来进行答案的统计
        }
    printf("%d\n", ans);
    return 0;
}
