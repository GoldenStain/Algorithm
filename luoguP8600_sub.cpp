#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define R(x) x = read()
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
#define lSon u<<1
#define rSon u<<1|1
using namespace std;

typedef long long LL;

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
       x = x * 10 + ch - '0';
       ch = getchar();
    }
     return x * f;
}

const int N = 50005;

LL ans;
int n, a[N];

struct treeNode{
    int l, r, minVal, cnt, addTag;
    // minVal存储max-min+l
}segTree[N << 2];

void pushUp(int u)
{
    segTree[u].minVal = min(segTree[lSon].minVal, segTree[rSon].minVal);
    int a = segTree[u].minVal==segTree[lSon].minVal?segTree[lSon].cnt:0,
        b = segTree[u].minVal==segTree[rSon].minVal?segTree[rSon].cnt:0;
    segTree[u].cnt = a + b;
}

void build(int u, int l, int r)
{
    segTree[u].addTag = 0;
    segTree[u].l = l;
    segTree[u].r = r;
    if(l == r)
    {
        segTree[u] = {l, r, l, 1, 0};
        return;
    }
    int mid = l + r >> 1;
    build(lSon, l, mid);
    build(rSon, mid + 1, r);
    pushUp(u);
}

void change(int u, int v)
{
    segTree[u].minVal += v;
    segTree[u].addTag += v;
}

void pushDown(int u)
{
    if(segTree[u].addTag == 0)
        return;
    change(lSon, segTree[u].addTag);
    change(rSon, segTree[u].addTag);
    segTree[u].addTag = 0;
}

void updateTree(int u, int l, int r, int val)
{
    if(segTree[u].l >= l && segTree[u].r <= r)
    {
        change(u, val);
        return;
    }
    pushDown(u);
    int mid = segTree[u].l + segTree[u].r >> 1;
    if(l <= mid) updateTree(lSon, l, r, val);
    if(r > mid) updateTree(rSon, l, r, val);
    pushUp(u);
}

int maxStk[N], maxTop, minStk[N], minTop;
//以maxStk为例，maxStk[maxTop]维护的是：[maxStk[maxTop - 1] + 1, maxStk[maxTop]]内的区间max
//单调栈和单调队列一样，存储的都是下标

void solve()
{
    build(1, 1, n);
    for(int i = 1; i <= n; i++)
    {
        //printf("%d\n", i);
        //维护maxStk
        while(maxTop && a[i] > a[maxStk[maxTop]])
        {
            updateTree(1, maxStk[maxTop - 1] + 1, maxStk[maxTop], a[i] - a[maxStk[maxTop]]);
            //如果maxTop=1,栈内只有一个元素，那么maxStk[maxTop - 1] + 1恰好是1,正好就改变了整个区间的max值，这是符合预期的，因此不需要特判
            //printf("case 1:updateTree(1, %d, %d, %d)\n", maxStk[maxTop - 1] + 1, maxStk[maxTop], a[i] - a[maxStk[maxTop]]);
            maxTop--;
        }
        //维护minStk
        while(minTop && a[i] < a[minStk[minTop]])
        {
            updateTree(1, minStk[minTop - 1] + 1, minStk[minTop], a[minStk[minTop]] - a[i]);
            //printf("case 2:updateTree(1, %d, %d, %d)\n", minStk[minTop - 1] + 1, minStk[minTop], a[minStk[minTop]] - a[i]);
            minTop--;
        }
        ans += segTree[1].cnt;
        maxStk[++maxTop] = minStk[++minTop] = i;
    }
}

int main()
{
    R(n);
    For(i, 1, n)
        R(a[i]);
    solve();
    printf("%lld\n", ans);
    return 0;
}
