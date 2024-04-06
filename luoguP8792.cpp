#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int gcd(int x, int y)
{
    return y?gcd(y, x%y):x;
}

int n, a[N];
int st[N][17];
int Log[N];
int cnt;

void build_st()
{
    Log[0] = -1;
    for(int i = 1; i <= n; i++)
        Log[i] = Log[i/2] + 1;
    for(int i = 1; i <= n; i++)
        st[i][0] = a[i];
    for(int k = 1; k <= 16; k++)
        for(int i = 1; i + (1 << (k - 1)) <= n; i++)
            st[i][k] = gcd(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
}

int query(int l, int r)
{
    if(r < l)
        return 0x3f3f3f3f;
    int t = Log[r - l + 1];
    return gcd(st[l][t], st[r - (1 << t) + 1][t]);
}

int solve()
{
    int ans = n;
    if(query(1, n) > 1)
        return -1;
    if(cnt)
        return n - cnt;
    /*int i = 1;
    for(int j = 1; j <= n; j++)
    {
        while(i < j && query(i + 1, j) == 1)
            i++;
        //cout << "R:" << i << " " << j << endl;
        if(query(i, j) == 1)
            ans = min(ans, j - i + 1);
    }*/
    int i = 1, j = n;
    while(query(i, j - 1) == 1)
        j--;
    while(query(i + 1, j) == 1)
        i++;
    n = j - i + 1;
    return ans + n - 2;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", &a[i]), cnt += (a[i] == 1);
    build_st();
    printf("%d\n", solve());
    return 0;
}
