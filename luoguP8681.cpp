#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int a[N], n, st = 1, ans, maxval;

void init()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
}

int get_sum(int lv)
{
    int res = 0;
    for(int i = lv; i < min(lv * 2, n + 1); i++)
    {
        if(i > n)
        {
            puts("impossible");
            return -1;
        }
        res += a[i];
    }
    return res;
}

int main()
{
    init();
    int depth = 1;
    while(st < n)
    {
        int t = get_sum(st);
        if(t > maxval)
        {
            ans = depth;
            maxval = t;
        }
        st *= 2;depth++;
    }
    printf("%d\n", ans);
    return 0;
}
