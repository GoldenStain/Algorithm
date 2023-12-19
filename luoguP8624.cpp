#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

int n, m, op[7];

struct Matrix
{
    int x, y;
    int **M;
    Matrix(int i, int j)
    {
        x = i;
        y = j;
        M = new int *[x + 1];
        for (int i = 1; i <= x; i++)
            M[i] = new int[y + 1];
    }
    Matrix *operator*(Matrix &t)
    {
        Matrix *tmp = new Matrix(6, 6);
        for (int i = 1; i <= x; i++)
            for (int j = 1; j <= t.y; j++)
            {
                int int_tmp = 0;
                for (int k = 1; k <= y; k++)
                    int_tmp = ((ll)int_tmp + (ll)M[i][k] * (ll)t.M[k][j]) % mod;
                tmp->M[i][j] = int_tmp;
            }
        return tmp;
    }
};

Matrix *quick_power(Matrix *a, int x)
{
    Matrix *tmp = new Matrix(6, 6);
    for(int i = 1; i <= 6; i++)
        for(int j = 1; j <= 6; j++)
            if(i == j)tmp->M[i][j] = 1;
            else tmp->M[i][j] = 0;
    while (x)
    {
        if (x & 1)
            tmp = (*tmp) * (*a);
        a = (*a) * (*a);
        x >>= 1;
    }
    return tmp;
}

signed main()
{
    op[1] = 4;
    op[4] = 1;
    op[2] = 5;
    op[5] = 2;
    op[3] = 6;
    op[6] = 3;
    cin >> n >> m;
    Matrix *st = new Matrix(1, 6), *mult = new Matrix(6, 6);
    For(i, 1, 6)
        For(j, 1, 6)
            mult->M[i][j] = 4;
    For(i, 1, 6) st->M[1][i] = 4;
    For(i, 1, m)
    {
        int a, b;
        cin >> a >> b;
        mult->M[a][op[b]] = 0;
        mult->M[b][op[a]] = 0;
    }
    st = (*st) * (*quick_power(mult, n - 1));
    int ans = 0;
    for(int i = 1; i <= 6; i++)
        ans = (ans + st->M[1][i]) % mod;
    cout << ans << endl;
    return 0;
}
