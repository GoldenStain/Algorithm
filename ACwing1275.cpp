#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 2e5 + 1;
typedef long long LL;

int m, p, q, n;
char op[2];

int a[N];

struct node {
    int l, r;
    int m;
} tr[N << 2];

void build(int u, int l, int r)
{
    tr[u] = {l, r};
    if(l == r)
        return;
    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void pushup(int u)
{
    tr[u].m = max(tr[u << 1].m, tr[u << 1 | 1].m);
}

void modify(int now, int k, int val)
{
    if(tr[now].l == tr[now].r)
    {
        tr[now].m = val;
        return;
    }
    int mid = (tr[now].l + tr[now].r) >> 1;
    if(k <= mid)
        modify(now << 1, k, val);
    else    
        modify(now << 1 | 1, k, val);
    pushup(now);
}

int query(int now, int l, int r)
{
    if(tr[now].l >= l && tr[now].r <= r)
        return tr[now].m;
    int mid = (tr[now].l + tr[now].r) >> 1;
    int res = 0;//要设置一个初值，否则在l > mid的情况下就会出错
    if(l <= mid)
        res = query(now << 1, l, r);
    if(r > mid)
        res = max(res, query(now << 1 | 1, l, r));
    return res;
}

int main()
{
    scanf("%d%d", &m, &p);
    int x;
    build(1, 1, m);
    while(m--)
    {
        scanf("%s%d", op, &x);
        if(*op == 'A')
        {
            n++;
            modify(1, n, ((LL)x + q) % p);
            //如果是(LL)(x + q)就不行，因为x + q已经把int溢出了，这时候再转换long long已经来不及了
        }
        else
        {
            printf("%d\n", (q = query(1, n - x + 1, n)));
        }
    }
    return 0;
}
