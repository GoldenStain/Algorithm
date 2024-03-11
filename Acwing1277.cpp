#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

typedef long long LL;

const int N = 1e5 + 5;

int n, m, P, a[N];

struct node{
    int l, r;
    int add, mul, sum;
}tr[N<<2];

void pushup(node &u, node &l, node &r)
{
    u.sum = ((LL)l.sum + r.sum) % P;
}

void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void pushdown(node &u, node &l, node &r)
{
    l.sum = ((LL)l.sum * u.mul + (LL)u.add * (l.r - l.l + 1)) % P;
    l.mul = (LL)l.mul * u.mul % P;
    l.add = (LL)l.add * u.mul % P;
    l.add = (LL)l.add + u.add % P;
    r.sum = ((LL)r.sum * u.mul + (LL)u.add * (r.r - r.l + 1)) % P;
    r.mul = (LL)r.mul * u.mul % P;
    r.add = (LL)r.add * u.mul % P;
    r.add = (LL)r.add + u.add % P;
    u.add = 0; u.mul = 1;
}

void pushdown(int u)
{
    pushdown(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r)
{
    if(l == r)
    {
        tr[u] = {l, r, 0, 1, a[l]};
        return;
    }
    tr[u] = {l, r, 0, 1, 0};
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

void modify(int u, int l, int r, int m, int a)
{
    if(tr[u].l >= l && tr[u].r <= r)
    {
        tr[u].sum = ((LL)tr[u].sum * m + (LL)a * (tr[u].r - tr[u].l + 1)) % P;
        tr[u].mul = (LL)m * tr[u].mul % P;
        tr[u].add = (LL)m * tr[u].add % P;
        tr[u].add = (LL)a + tr[u].add % P;
        return;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if(l <= mid) modify(u << 1, l, r, m, a);
    if(r > mid) modify(u << 1 | 1, l, r, m, a);
    pushup(u);
}

int query(int u, int l, int r)
{
    if(tr[u].l >= l && tr[u].r <= r)
        return tr[u].sum;
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int res = 0;
    if(l <= mid) res = ((LL)res + query(u << 1, l, r)) % P;
    if(r > mid) res = ((LL)res + query(u << 1 | 1, l, r)) % P;
    return res;
}

int main()
{
    scanf("%d%d", &n, &P);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    scanf("%d", &m);
    build(1, 1, n);
    int l, r, c, flag;
    while(m--)
    {
        scanf("%d", &flag);
        if(flag == 1)
        {
            scanf("%d%d%d", &l, &r, &c);
            modify(1, l, r, c, 0);
        }
        else if(flag == 2)
        {
            scanf("%d%d%d", &l, &r, &c);
            modify(1, l, r, 1, c);
        }
        else
        {
            scanf("%d%d", &l, &r);
            printf("%d\n", query(1, l, r));
        }
    }
    return 0;
}
