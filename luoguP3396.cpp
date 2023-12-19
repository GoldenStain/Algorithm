#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <cmath>
#define RED "\033[0;32;31m"
#define NONE "\033[m"
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
typedef long long ll;

const int N = 150005, M = 390;
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
        x = x * 10 + ch - '0', ch = getchar();
    return x;
}

int n, f[N][M], a[N], m;
char c[5];

int main()
{
    R(n);
    R(m);
    int mn = sqrt(n);
    For(i, 1, n)
        R(a[i]);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= mn; j++)
            f[j][i % j] += a[i];
    int x, y;
    while (m--)
    {
        scanf("%s", c);
        R(x);
        R(y);
        if (c[0] == 'A')
        {
            if (x <= mn)
                printf("%d\n", f[x][y]);
            else
            {
                int sum = 0;
                for (int i = y; i <= n; i += x)
                    sum += a[i];
                printf("%d\n", sum);
            }
        }
        else
        {
            for (int i = 1; i <= mn; i++) // 更新第x个数所涉及到的所有的池
                f[i][x % i] += y - a[x];
            a[x] = y;
        }
    }
    return 0;
}
