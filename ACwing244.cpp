#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int lowbit(int x)
{
    return x & (-x);
}

int n, a[N], tr[N], h[N];

void modify(int k, int x)
{
    for(int i = k; i <= n; i += lowbit(i))
        tr[i] += x;
}

int query(int k)
{
    int res = 0;
    for(int i = k; i; i -= lowbit(i))
        res += tr[i];
    return res;
}

int find(int x)
{
    int l = 1, r = n;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(query(mid) >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}

void init()
{
    for(int i = 1; i <= n; i++)
        modify(i, 1);
}

int main()
{
    scanf("%d", &n);
    for(int i = 2; i <= n; i++)
        scanf("%d", &a[i]);
    init();
    for(int i = n; i >= 1; i--)
    {
        int pos = find(a[i] + 1);
        h[i] = pos;
        modify(pos, -1);
    }
    for(int i = 1; i <= n; i++)
        printf("%d\n", h[i]);
    return 0;
}
