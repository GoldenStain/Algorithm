#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;

int n, m;

LL a[N];

struct node{
    int l, r;
    LL sum, add;
}tr[N << 2];

void pushup(int u)
{
    int l = u << 1, r = u << 1 | 1;
    tr[u].sum = tr[l].sum + tr[r].sum;
}

void pushdown(int u)
{
    if(tr[u].add == 0)
        return;
    int l = u << 1, r = u << 1 | 1;
    tr[l].add += tr[u].add, tr[l].sum += (tr[l].r - tr[l].l + 1) * tr[u].add;
    tr[r].add += tr[u].add, tr[r].sum += (tr[r].r - tr[r].l + 1) * tr[u].add;
    tr[u].add = 0;
}

void build(int u, int l, int r)
{
    if(l == r)
    {
        tr[u] = {l, r, a[l], 0};
        return;
    }
    tr[u] = {l, r, 0, 0};
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int l, int r, int v)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].add += v;
        tr[u].sum += (LL)v * (tr[u].r - tr[u].l + 1);
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if(l <= mid)
        modify(u << 1, l, r, v);
    if(r > mid)
        modify(u << 1 | 1, l, r, v);
    pushup(u);
}

LL query(int u, int l, int r)
{
    if(tr[u].l >= l && tr[u].r <= r)
        return tr[u].sum;
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    LL res = 0ll;
    if(l <= mid)
        res += query(u << 1, l, r);
    if(r > mid)
        res += query(u << 1 | 1, l, r);
    return res;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    build(1, 1, n);
    char op[2];
    while(m--)
    {
        int l, r, d;
        scanf("%s", op);
        if(*op == 'C')
        {
            scanf("%d%d%d", &l, &r, &d);
            modify(1, l, r, d);
        }
        else
        {
            scanf("%d%d", &l, &r);
            printf("%lld\n", query(1, l, r));
        }
    }
    return 0;
}
