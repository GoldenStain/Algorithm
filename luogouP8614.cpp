#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 1005, mod = 100000007;

int n, s, a, b;
int dp[N * N];

int main()
{
    cin >> n >> s >> a >> b;
    int k = n * (n - 1) / 2;
    dp[0] = 1;
    for(int i = 1; i < n; i++)
        for(int j = k; j >= i; j--)
            dp[j] = (dp[j] + dp[j - i]) % mod;
    int ans = 0;
    for(int i = 0; i <= k; i++)
        if((long long)((long long)s + (long long)b * (long long)k - (a + b) * i) % n == 0)
            ans = (ans + dp[i]) % mod;
    cout << ans << endl;
    system("pause");
    return 0;
}
