#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
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

const int N = 5005;

char s[N];

bool check(int l, int r)
{
    int i = l, j = r;
    while(i < j)
        if(s[i] == s[j])
        {
            i++;
            j--;
        }
        else
            return s[j] < s[i];
    return 0;
}

int solve()
{
    int res = 0;
    int Len = strlen(s);
    for(int l = 0; l < Len - 1; l++)
        for(int r = l + 1; r < Len; r++)
            if(check(l, r))
                res++;
    return res;
}

int main()
{
    scanf("%s", s);
    printf("%d\n", solve());
    return 0;
}
