#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define R register
using namespace std;
const int N = 1e4 + 5, M = 5e3 + 5;
int n, m;
int g[M][M];
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
int x_max, y_max;
int main()
{
    n = read();
    m = read();
    for (R int i = 1; i <= n; i++)
    {
        int x = read() + 1;
        int y = read() + 1;
        int v = read();
        x_max = max(x, x_max);
        y_max = max(y, y_max);
        g[x][y] += v;
    }
    for (R int i = 1; i <= x_max; i++)
        for (R int j = 1; j <= y_max; j++)
        {
            g[i][j] += g[i - 1][j] + g[i][j - 1] - g[i - 1][j - 1];
        }
    int ans = 0;
    for (R int i = m; i <= x_max; i++)
        for (R int j = m; j <= y_max; j++)
        {
            int stx = i - m + 1, sty = j - m + 1;
            int tmp = g[i][j] - g[i][sty - 1] - g[stx - 1][j] + g[stx - 1][sty - 1];
            ans = max(tmp, ans);
        }
    printf("%d", ans);
    return 0;
}