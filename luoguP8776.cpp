#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <cmath>
#define RT register
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 1e5 + 5;

int n, k;

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

int a[N], down_pre[N], up_len[N], down_len[N], en[N], id[N]; // id是反着做的辅助数组

void dp()
{
    // 正着做
    int res = 1;
    en[1] = a[1];
    up_len[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (a[i] >= en[res])
        {
            en[++res] = a[i];
            up_len[i] = res;
        }
        else
        {
            int pos = upper_bound(en + 1, en + res + 1, a[i]) - en;
            en[pos] = a[i];
            up_len[i] = pos;
        }
    }
    // for(int i = 1; i <= n; i++)
    //     cout << up_len[i] << " ";
    //  反着做
    res = 1;
    memset(en, 0, sizeof en);
    down_len[n] = 1;
    en[res] = -a[n];
    id[res] = n;
    for (int i = n - 1; i; i--)
    {
        int tmp = -a[i];
        if (tmp >= en[res])
        {
            down_pre[i] = id[res];
            en[++res] = tmp;
            id[res] = i;
            down_len[i] = res;
        }
        else
        {
            int pos = upper_bound(en + 1, en + res + 1, tmp) - en;
            en[pos] = tmp;
            down_len[i] = pos;
            down_pre[i] = id[pos - 1];
        }
    }
    /*for (int i = 1; i <= n; i++)
        cout << down_len[i] << " " << down_pre[i] << endl;*/
}

int tr[N], b[N], cnt;

int lowbit(int x)
{
    return x & (-x);
}

int query(int x)
{
    int res = -1;
    while (x)
    {
        res = max(res, tr[x]);
        x -= lowbit(x);
    }
    return res;
}

void add(int x, int k)
{
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] = max(tr[i], k);
}

int solve()
{
    memcpy(b, a, sizeof(a));
    sort(b + 1, b + n + 1);
    cnt = unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b + 1, b + n + 1, a[i]) - b;

    /*for (RT int i = 1; i <= n; i++)
        up_len[i] = query(a[i]) + 1, add(a[i], up_len[i]);
    memset(tr, 0, sizeof(tr));
    for (RT int i = n; i >= 1; i--)
        down_len[i] = query(n - a[i] + 1) + 1, add(n - a[i] + 1, down_len[i]);

    memset(tr, 0, sizeof(tr));*/
    int ans = 0;
    a[n + 1] = cnt + 1;
    for (int i = k + 2; i <= n + 1; i++)
    {
        add(a[i - k - 1], up_len[i - k - 1]);
        ans = max(ans, query(a[i]) + k + down_len[i]);
    }
    return ans;
}

//int b_up_len[N], b_down_len[N];

int main()
{
    R(n);
    R(k);
    if (k >= n - 1)
    {
        printf("%d\n", n);
        return 0;
    }
    for (int i = 1; i <= n; i++)
    {
        R(a[i]);
    }
    dp();
    //memcpy(b_up_len, up_len, sizeof(up_len));
    //memcpy(b_down_len, down_len, sizeof(down_len));
    printf("%d\n", solve());
    /*solve();
    int c = 0;
    for(int i = 1; i <= n; i++)
        if(b_down_len[i] != down_len[i])
            c++;
    cout << c << endl;*/
    return 0;
}