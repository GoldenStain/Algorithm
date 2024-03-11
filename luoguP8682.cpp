#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int n, maxn = -1, minn = 1e9 + 1;

int gcd(int a, int b)
{
    return b?gcd(b, a % b):a;
}

int main()
{
    scanf("%d", &n);
    int x = 0, y = 0, new_d = 0, old_d = 0, ans = 0;
    scanf("%d", &y);
    maxn = max(maxn, y);
    minn = min(minn, y);
    for(int i = 2; i <= n; i++)
    {
        scanf("%d", &x);
        new_d = abs(x - y);
        y = x;
        ans = gcd(ans, gcd(old_d, new_d));
        old_d = new_d;
        maxn = max(maxn, x);
        minn = min(minn, x);
    }
    if(ans == 0)
        printf("%d\n", n);
    else
        printf("%d\n", (maxn - minn) / ans + 1);
    return 0;
}
