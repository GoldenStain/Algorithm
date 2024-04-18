#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define R(x) x = read()
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

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

int l, r;

int f(int n)
{
    return (n + 1)/2 + n/4;
}

int main()
{
    R(l);R(r);
    printf("%d\n", f(r) - f(l - 1));
    return 0;
}
