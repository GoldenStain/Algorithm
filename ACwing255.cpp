#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstring>
#include <vector>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 1, M = 1e4 + 1;

struct node{
    int l, r;
    int cnt;
}tr[N * 4 + 17 * N];

int n, m, idx, a[N], root[N];
vector<int> num;

int build(int l, int r)
{
    int p = ++idx;
    tr[p].cnt = 0;
    if(l == r)
        return p;
    int mid = l + r >> 1;
    tr[p].l = build(l, mid);
    tr[p].r = build(mid + 1, r);
    return p;
}

int insert(int last, int l, int r, int tar)
{
    int now = ++idx;
    tr[now] = tr[last];
    if(l <= tar && r >= tar)
    {
        tr[now].cnt++;
        return now;
    }
    int mid = l + r >> 1;
    if(tar <= mid)
        tr[now].l = insert(tr[last].l, l, mid, tar);
    if(tar > mid)
        tr[now].r = insert(tr[last].r, mid + 1, r, tar);
    tr[now].cnt = tr[tr[now].l].cnt + tr[tr[now].r].cnt;
    return now;
}

int query(int L, int R, int l, int r, int k)
{
    if(l == r) 
        return l;
    int mid = l + r >> 1;
    int c = tr[tr[R].l].cnt - tr[tr[L].l].cnt;
    if(c < k)
        return query(tr[L].r, tr[R].r, mid + 1, r, k - c);
    else
        return query(tr[L].l, tr[R].l, l, mid, k);
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        num.push_back(a[i]);
    }
    sort(num.begin(), num.end());
    num.erase(unique(num.begin(), num.end()), num.end());
    root[0] = build(0, num.size() - 1);
    for(int i = 1; i <= n; i++)
        root[i] = insert(root[i - 1], 0, num.size() - 1, lower_bound(num.begin(), num.end(), a[i]) - num.begin());
    int l, r, k;
    while(m--)
    {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", num[query(root[l - 1], root[r], 0, num.size() - 1, k)]);
    }
    return 0;
}
