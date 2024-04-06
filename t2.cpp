#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <string.h>
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

const int N = 1005;

int n, m;
int g[N][N], f[N][N], ans[N][N];

void floyd()
{
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
            {
                //f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
                if(f[i][j] > f[i][k] + f[k][j])
                {
                    f[i][j] = f[i][k] + f[k][j];
                    ans[i][j] = k;
                }
            }
}

int path[N], cnt;

void solve(int a, int b)
{
    if(!ans[a][b])
        return;
    //path[++cnt] = a;
    solve(a, ans[a][b]);
    path[++cnt] = ans[a][b];
    solve(ans[a][b], b);
    //path[++cnt] = b;
}

void print_path(int a, int b)
{
    if(f[a][b] >= 1000000)
    {
        puts("can not reach");
        return;
    }
    memset(path, 0, sizeof(path));
    cnt = 0;
    path[++cnt] = a;
    solve(a, b);
    path[++cnt] = b;
    printf("the path between %d and %d\n", a, b);
    for(int i = 1; i <= cnt; i++)
        printf("%d ", path[i]);
    puts("");
}

int main()
{
    R(n);R(m);
    memset(f, 0x3f, sizeof(f));
    For(i, 1, m)
    {
        f[i][i] = 0;
    }
    For(i, 1, m)
    {
        int a, b, c;
        R(a);R(b);R(c);
        f[a][b] = min(f[a][b], c);
    }
    floyd();
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
            {
                puts("the same point");
                continue;
            }
            print_path(i, j);
        }
    return 0;
}
