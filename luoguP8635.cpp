#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

int n, a[4], rtn;

bool dfs(int now, int st)
{
    if(now == 3)
    {
        int k = n - a[1] * a[1] - a[0] * a[0] - a[2] * a[2], rk = sqrt(k);
        if(rk * rk == k)
        {
            a[3] = rk;
            return true;
        }
        return false;
    }
    for(int i = st; i <= rtn; i++)
    {                         
        a[now] = i;
        if(dfs(now + 1, i))
            return true;
        a[now] = 0;
    }
    return false;
}

int main()
{
    cin >> n;
    rtn = sqrt(n) + 1;
    dfs(0, 0);
    sort(a, a + 4);
    for(int i = 0; i < 4; i++)
     cout << a[i] << ' ';
    return 0;
}
