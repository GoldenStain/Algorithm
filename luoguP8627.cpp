#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

int n;

int main()
{
    int ans = 0, res = 0;
    cin >> n;
    ans += n;
    while(n)
    {
        int t = n/3;
        ans += t;
        res += n - t * 3;
        n = t;
        if(res >= 3)
        {
            res %= 3;
            ans++;
            n++;
        }
    }
    cout << ans << endl;
    return 0;
}
