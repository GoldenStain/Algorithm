#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <string.h>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 20, M = 1 << 18;
const double eps = 1e-8;

void equation(double &x, double &y, double a1, double b1, double c1, double a2, double b2, double c2)
{ // 解方程
    y = (a1 * c2 - a2 * c1) / (a1 * b2 - a2 * b1);
    x = (c1 - b1 * y) / a1;
}

bool Equal(double a, double b)
{
    if (fabs(a - b) < eps)
        return true;
    return false;
}

bool check(double x, double y, double a, double b)
{
    return Equal(y, a * x * x + b * x);
}

// equation(a,b,x[i]*x[i],x[i],y[i],x[j]*x[j],x[j],y[j]);

int t, n, m;
int Connection[N][N], f[M], first_zero[M];
double x[N], y[N];

int lowbit(int x)
{
    return x & (-x);
}

void print(int x)
{
    for (int i = 7; i >= 0; i--)
        cout << ((x >> i) & 1);
    cout << endl;
}

int Log[M];

void get_zero()
{
    /*for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < 18; j++)
        {
            if (!((i >> j) & 1))
            {
                first_zero[i] = j;
                break;
            }
        }
    }*/
    Log[0] = -1;
    For(i, 1, M)
        Log[i] = Log[i >> 1] + 1;
    for(int i = 0; i < M; i++)
    {
        int t = ~i;
        t = lowbit(t);
        first_zero[i] = Log[t];
    }
}

void init()
{
    double a, b;
    memset(Connection, 0, sizeof(Connection));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            if (i == j)
            {
                Connection[i][i] = 1 << (i - 1);
                continue;
            }
            if (Equal(x[i], x[j]))
                continue;
            equation(a, b, x[i] * x[i], x[i], y[i], x[j] * x[j], x[j], y[j]);
            if (a > -eps)
                continue;
            for (int k = 1; k <= n; k++)
                if (check(x[k], y[k], a, b))
                    Connection[i][j] |= 1 << (k - 1);
        }
}

int dp()
{
    memset(f, 0x3f, sizeof(f));
    f[0] = 0;
    for (int st = 0; st < 1 << n; st++)
    {
        int p = first_zero[st];
        for (int i = 1; i <= n; i++)
        {
            int t = st | Connection[p + 1][i];
            f[t] = min(f[t], f[st] + 1);
        }
    }
    return f[(1 << n) - 1];
}

int main()
{
    get_zero();
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        For(i, 1, n)
            scanf("%lf%lf", &x[i], &y[i]);
        init();
        printf("%d\n", dp());
    }
    return 0;
}
