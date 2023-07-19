#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int N = 300005;

int s[N], ans, n, q[N], m;
int hh , tt;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
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

int main()
{
    n = read(); m = read(); 
    for(int i = 1; i <= n; i++)
    {
        s[i] = read();
        s[i] += s[i - 1];
        //printf("%d ", s[i]);
    }
    //putchar('\n');
    ans = s[1];
    for(int i = 1;i <= n; i++)
    {
        if(q[hh] < i - m) hh++;
        ans = max(ans, s[i] - s[q[hh]]);
        while(hh <= tt && s[q[tt]] >= s[i]) tt--;
        q[++tt] = i;
    }
    printf("%d\n", ans);
    return 0;
}