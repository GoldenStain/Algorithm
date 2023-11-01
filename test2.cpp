#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#define R register
using namespace std;
const int N = 255;
int g[N][N];
int f[N][N];
int n, m, res;
int main()
{
    scanf("%d%d", &n, &m);
    for (R int i = 1; i <= n; i++)
        for (R int j = 1; j <= m; j++)
        {
            scanf("%d", &g[i][j]);
            if (g[i][j])
            {
                f[i][j] = min(f[i-1][j-1],min(f[i-1][j],f[i][j-1])) + 1;
            }
            res = max(res, f[i][j]);
        }
    printf("%d", res);
    return 0;
}