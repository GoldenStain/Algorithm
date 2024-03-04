#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

int k, tar;
long long ans;

int powers[] = {1, 10, 100, 1000, 10000};

void solve(int n, int res, int last, bool suc)
{
    if(res > tar) return;
    if(n == k + 1)
    {
        // cout << res << " "  << " " << suc << endl;
        if(suc)
            ans += res;
        return;
    }
    for(int i = 0; i <= 9; i++)
    {
        bool f = false;
        if(i == 1 || i == 2 || i == 9)  f = true;
        if(i > 0 && last == 0)   f = true;
        solve(n + 1, res + i * powers[n - 1], i, suc | f);
    }
}

int main()
{
    cin >> tar;
    k = log10(tar) + 1;
    solve(1, 0, -1, 0);
    cout << ans << endl;
    return 0;
}
