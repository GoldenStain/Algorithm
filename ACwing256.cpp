#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 6e5 + 5, M = N * 24;

int n, m, a[N], idx, tr[M][2], root[N], max_id[M];

void insert(int ver, int now, int last, int k)
{
    if(k < 0)
    {
        max_id[now] = ver;
        return;
    }
    int v = a[ver] >> k & 1;
    if(last)
        tr[now][v ^ 1] = tr[last][v ^ 1];
    tr[now][v] = ++idx;
    insert(ver, tr[now][v], tr[last][v], k - 1);
    max_id[now] = max(max_id[tr[now][0]], max_id[tr[now][1]]);
}

int query(int left, int right, int x)
{
    int pos = root[right];
    for(int k = 23; k >= 0; k--)
    {
        int v = x >> k & 1;
        if(max_id[tr[pos][v ^ 1]] >= left)
            pos = tr[pos][v ^ 1];
        else
            pos = tr[pos][v];
    }
    return x ^ a[max_id[pos]];
}

int main()
{
    scanf("%d%d", &n, &m);
    root[0] = ++idx;
    max_id[0] = -1;
    insert(0, idx, 0, 23);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        a[i] ^= a[i - 1];
        root[i] = ++idx;
        insert(i, root[i], root[i - 1], 23);
    }
    char op[2];
    int l, r, x;
    while(m--)
    {
        scanf("%s", op);
        if(*op == 'A')
        {
            n++;
            scanf("%d", &a[n]);
            root[n] = ++idx;
            a[n] ^= a[n - 1];
            insert(n, root[n], root[n - 1], 23);
        }
        else
        {
            scanf("%d%d%d", &l, &r, &x);
            printf("%d\n", query(l - 1, r - 1, a[n] ^ x));
        }
    }
    return 0;
}
