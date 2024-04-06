#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 15, K = 105, M = 1 << 10;
typedef long long LL;
typedef unsigned long long ULL;

int n, k;
vector<int> LegalStates;
vector<int> Transformation[M];

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

inline int lowbit(int x)
{
    return x & (-x);
}

int cnt[M];

bool check(int a, int b)
{
    if (a & b)
        return 1;
    int t = a | b;
    if (t & (t >> 1))
        return 1;
    return 0;
}

void init()
{
    for (int i = 0; i < (1 << n); i++)
    {
        if (i & (i >> 1))
            continue;
        LegalStates.push_back(i);
        int t = i;
        while (t)
        {
            cnt[i]++;
            t -= lowbit(t);
        }
    }
    // Transformation.resize((1 << n), vector<int>(0, 0));
    for (int a : LegalStates)
    {
        for (int j : LegalStates)
        {
            if (!check(a, j))
                Transformation[a].push_back(j);
        }
    }
}

LL f[2][K][M];

LL dp() // 答案会爆int，结果f数组改成long long之后dp函数忘记由int改为long long了，八嘎
{
    f[0][0][0] = 1ll;
    for (int i = 1; i <= n + 1; i++)
        for (int st : LegalStates)
        {
            for (int c = cnt[st]; c <= k; c++)
            {
                f[i & 1][c][st] = 0; //采用滚动数组，这里记得要先清零，否则会重复在同一个位置多次累加，导致答案偏大
                int lc = c - cnt[st];
                for (int j : Transformation[st])
                    f[i & 1][c][st] += f[(i - 1) & 1][lc][j];
            }
        }

    return f[(n + 1) & 1][k][0];
}

int main()
{
    R(n);
    R(k);
    init();
    /*for(int i : LegalStates)
    {
        cout << i << " " << cnt[i] << endl;
        cout << "K:";
        for(int j : Transformation[i])
            cout << j << " ";
        cout << endl;
    }*/
    printf("%lld\n", dp());
    return 0;
}
