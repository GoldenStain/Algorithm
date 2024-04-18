#include <bits/stdc++.h>
#define R(x) x=read()
using namespace std;

inline int read()
{
    int x = 0, f = 1;char ch = getchar();
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

const int N = 1e5 + 5, M = 2e5 + 5;

struct Element{
    int a, b, c, cnt, res;
    bool operator != (const Element &tmp) const
    {
        if(a != tmp.a) return true;
        if(b != tmp.b) return true;
        if(c != tmp.c) return true;
        return false;
    }
};

bool cmpA(Element x, Element y)
{
    if(x.a != y.a)  return x.a < y.a;
    if(x.b != y.b)  return x.b < y.b;
    return x.c < y.c;
}

Element e[N], re[N];

int n, k, idx;

//树状数组

int lowbit(int x)
{
    return x & -x;
}

int tr[M];

void update(int x, int v)
{
    for(int i = x; i <= k; i+=lowbit(i))
        tr[i] += v;
    return;
}

int query(int x)
{
    int res = 0;
    for(int i = x; i; i-=lowbit(i))
        res += tr[i];
    return res;
}

//临时数组
Element tmpE[N];

bool cmpB(Element x, Element y)
{
    if(x.b != y.b)  return x.b < y.b;
    return x.c < y.c;
}

void solve(int l, int r)
{
    if(l == r)
        return;
    int mid = l + r >> 1;
    solve(l, mid); solve(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    /*while(i <= mid && j <= r)
    {
        if(re[i].b <= re[j].b) 
        {
            update(re[i].c, re[i].cnt);
            re[j].res += query(re[j].c);
            tmpE[k++] = re[i++];
        }
        else
        {
            tmpE[k++] = re[j++];
        }
    }   
    int bI = i;
    while(i <= mid) 
    {
        tmpE[k++] = re[i++];
    }
    while(j <= r)
    {
        re[j].res += query(re[j].c);
        tmpE[k++] = re[j++];
    }
    for(i = l; i <= r; i++)
    {
        if(i < bI)
            update(re[i].c, -re[i].cnt);
        re[i] = tmpE[i];
    }*/
    while(j <= r)
    {
        while(i <= mid && re[i].b <= re[j].b)
        {
            update(re[i].c, re[i].cnt);
            tmpE[k++] = re[i];
            i++;
        }
        re[j].res += query(re[j].c);
        tmpE[k++] = re[j++];
    }
    for(int iI = l; iI < i; iI++)
        update(re[iI].c, -re[iI].cnt);
    while(i <= mid)
        tmpE[k++] = re[i++];
    for(i = l; i <= r; i++)
        re[i] = tmpE[i];
    //sort(re + l, re + r + 1, cmpB);
}

int ans[N];

int main()
{
    R(n);R(k);
    for(int i = 1; i <= n; i++)
    {
        R(e[i].a);R(e[i].b);R(e[i].c);
    }
    //去重
    sort(e + 1, e + n + 1, cmpA);
    int tmpCnt = 0;
    for(int i = 1; i <= n; i++)
    {
        tmpCnt++;
        if(e[i] != e[i + 1])
        {
            re[++idx] = e[i];
            re[idx].cnt = tmpCnt;
            re[idx].res = 0;
            tmpCnt = 0;
        }
    }
    solve(1, idx);
    for(int i = 1; i <= idx; i++)
        ans[re[i].cnt - 1 + re[i].res] += re[i].cnt;
    for(int i = 0; i < n; i++)
        printf("%d\n", ans[i]);
    return 0;
}