#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
using namespace std;

typedef long long ll;

const int P = 1e9 + 7;

struct F
{
    int s0, s1, s2;
} f[20][10][7][7];

int T;

int power7[20], powerP[20];

int mod(ll x, int y)
{
    return (x % y + y) % y;
}

void init()
{
    power7[0] = powerP[0] = 1;
    for (int i = 1; i <= 18; i++)
    {
        power7[i] = power7[i - 1] * 10 % 7;
        powerP[i] = powerP[i - 1] * 10ll % P;
    }
    for (int i = 0; i <= 9; i++)
    {
        if (i == 7)
            continue;
        F &tmp = f[1][i][i % 7][i % 7];
        tmp.s0++;
        tmp.s1 += i;
        tmp.s2 += i * i;
    }
    ll power = 10;
    for (int i = 2; i <= 19; i++, power *= 10ll)
    {
        for (int j = 0; j <= 9; j++)
        {
            if (j == 7)
                continue;
            for (int a = 0; a < 7; a++)
                for (int b = 0; b < 7; b++)
                {
                    for (int k = 0; k <= 9; k++)
                    {
                        if (k == 7)
                            continue;
                        auto &v1 = f[i][j][a][b], &v2 = f[i - 1][k][mod(a - j * power, 7)][mod(b - j, 7)];
                        v1.s0 = mod(v1.s0 + v2.s0, P);
                        v1.s1 = mod(v1.s1 + v2.s1 + j * (power % P) % P * v2.s0, P);
                        v1.s2 = mod(v1.s2 + j * j * (power % P) % P * (power % P) % P * v2.s0 + v2.s2 + 2 * j * power % P * v2.s1, P);
                    }
                }
        }
    }
}

F get(int i, int j, int a, int b)
{
    int s0 = 0, s1 = 0, s2 = 0;
    for (int x = 0; x < 7; x++)
        for (int y = 0; y < 7; y++)
            if (x != a && y != b)
            {
                F v = f[i][j][x][y];
                s0 = (s0 + v.s0) % P;
                s1 = (s1 + v.s1) % P;
                s2 = (s2 + v.s2) % P;
            }
    return {s0, s1, s2};
}

int num[20];

int resolve(ll x)
{
    int res = 0;
    if (!x)
        return 0;
    int len = 0;
    ll back_up = x % P;
    while (x)
    {
        num[++len] = x % 10;
        x /= 10;
    }
    ll last_a = 0, last_b = 0;
    for (int i = len; i; i--)
    {
        int tmp = num[i];
        for (int j = 0; j < tmp; j++)
        {
            if (j == 7)
                continue;
            int a = mod(-last_a * power7[i], 7);
            int b = mod(-last_b, 7);
            F v = get(i, j, a, b);
            res = mod(
                res +
                    (last_a % P) * (last_a % P) % P * powerP[i] % P * powerP[i] % P * v.s0 % P +
                    v.s2 +
                    2 * last_a % P * powerP[i] % P * v.s1,
                P);
        }
        if (tmp == 7)
            break;
        last_a = last_a * 10 + tmp;
        last_b += tmp;
        if (i == 1 && last_a % 7 && last_b % 7)
            res = mod(res + back_up * back_up , P);
    }
    return res;
}

int main()
{
    ll L, R;
    scanf("%d", &T);
    init();
    while (T--)
    {
        scanf("%lld%lld", &L, &R);
        printf("%d\n", mod(resolve(R) - resolve(L - 1), P));
    }
    return 0;
}