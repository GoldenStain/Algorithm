#include <bits/stdc++.h>
#define R(x) x = read()
#define RLL(x) x = readLL()
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

inline int read()
{
    int x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x*f;
}

inline LL readLL()
{
    LL x = 0, f = 1; char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-')
        {
            f = -1;
        }
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x*f;
}

int n, m, q;
int fa[N];
LL dis[N];

int find(int x)
{
    if(x == fa[x])
        return x;
    int oldFa = fa[x];
    fa[x] = find(fa[x]);
    dis[x] += dis[oldFa];
    return fa[x];
}

void init()
{
    for(int i = 1; i <= n; i++)
        fa[i] = i;
}

void printLL(LL x)
{
    if(x < 0)
    {
        putchar('-');
        x = -x;
    }
    if(x > 9)
        printLL(x/10);
    putchar(x%10+'0');
    return;
}

int main()
{
    R(n);R(m);R(q);
    init();
    for(int i = 1; i <= m; i++)
    {
        int l, r; LL s;
        R(l);R(r);RLL(s);
        l--;
        int fL = find(l), fR = find(r);
        if(fL == fR)
            continue;
        LL a = dis[l], b = dis[r];
        fa[fL] = fR;
        dis[fL] = s + b -a;
    }
    for(int i = 1; i <= q; i++)
    {
        int l, r;
        R(l);R(r);
        l--;
        int fL = find(l), fR = find(r);
        if(fL != fR)
            puts("UNKNOWN");
        else
            {printLL(dis[l] - dis[r]); puts("");}
    }
    return 0;
}