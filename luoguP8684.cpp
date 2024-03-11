#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

typedef long long LL;

const int N = 3e5 + 5;

int T, n;
LL s[N];

int main()
{
    scanf("%d", &T);
    LL l, r, ans;
    while(T--)
    {
        ans = 0;
        scanf("%d", &n);
        s[0] = 0;
        for(int i = 1; i <= n; i++)
        {
            scanf("%lld", s + i);
            s[i] += s[i - 1];
        }
        sort(s + 1, s + n);
        if(s[0] > s[n])
            swap(s[0], s[n]);
        l = s[0];
        int m = lower_bound(s + 1, s + n, l) - s;
        r = s[m];
        for(int i = m - 1; i; i--)
        {
            if(l > r)
                swap(l, r);
            ans = max(ans, r - s[i]);
            r = s[i];
        }
        ans = max(ans, abs(r - l));
        l = s[m]; r = s[n];
        for(int i = m + 1; i < n; i++)
        {
            if(l > r)
                swap(l, r);
            ans = max(ans, s[i] - l);
            l = s[i];
        }
        ans = max(ans, abs(r - l));
        printf("%lld\n", ans);
    }    
    return 0;
}
