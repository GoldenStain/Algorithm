#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 1e6 + 9, p = 998244353;

int a[N], prefix[N];

signed main()
{
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;cin >> n;
    for(int i = 1;i <= n; ++ i)cin >> a[i];
    for(int i = 1;i <= n; ++ i)prefix[i] = prefix[i - 1] + a[i];

    if(prefix[n] < 0)
    {
        cout << -1 << '\n';
        return 0;
    }
    //遇到的第一个是负数
    for(int i = 1;i <= n; ++ i)
    {
        if(prefix[i] != 0)
        {
            if(prefix[i] < 0)
            {
                cout << -1 << '\n';
                return 0;
            }
            break;
        }   
    }

    int ans = 0, res = 0, mx = 0;
    //前面一步步推进
    for(int i = 1;i <= n; ++ i)
    {
        mx = max(mx, prefix[i]);
        res += prefix[i];
        ans ++;//走一秒
        if(res < 0)//说明走快了，应该在前面多停留一段时间的
        {
            //补几秒钟
            int ti = (-res + mx - 1) / mx;
            ans += ti;
            res += ti * mx;
        }
    }
    cout << ans << '\n';
    return 0;
}
