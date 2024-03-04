#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 500001, M = 100001;

int n, m, a[N];

struct node{
    int l, r;
    int ans, maxf, maxb, sum;
} tr[N << 2];

void pushup(node &u, node l, node r)
{
    u.sum = l.sum + r.sum;
    u.ans = max(max(l.ans, r.ans), l.maxb + r.maxf);
    u.maxf = max(l.maxf, l.sum + r.maxf);
    u.maxb = max(r.maxb, r.sum + l.maxb);
}

void pushup(int u)
{
    pushup(tr[u], tr[u << 1], tr[u << 1 | 1]);
}

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    if(l == r)
    {
        tr[u].sum = a[l];
        tr[u].maxf = a[l];
        tr[u].maxb = a[l];
        tr[u].ans = a[l];
        return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    pushup(u);
}

node query(int u, int l, int r)
{
    if(tr[u].l >= l && tr[u].r <= r)
        return tr[u];
    int mid = tr[u].l + tr[u].r >> 1;
    if(r <= mid)
        return query(u << 1, l, r);
    if(l > mid)
        return query(u << 1 | 1, l, r);
    node res;
    pushup(res, query(u << 1, l, r), query(u << 1 | 1, l, r));
    return res;
}

void modify(int u, int k, int x)
{
    if(tr[u].l == tr[u].r)
    {
        tr[u].sum = x;
        tr[u].maxf = x;
        tr[u].maxb = x;
        tr[u].ans = x;
        return;
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if(k <= mid)
        modify(u << 1, k, x);
    else
        modify(u << 1 | 1, k, x);
    pushup(u);
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    build(1, 1, n);
    int op, x, y;
    while(m--)
    {
        scanf("%d", &op);
        if(op == 1)
        {
            scanf("%d%d", &x, &y);
            if(x > y)   swap(x, y);
            printf("%d\n", query(1, x, y).ans);
        }
        else
        {
            scanf("%d%d", &x, &y);
            modify(1, x, y);
        }
    }
    return 0;
}
