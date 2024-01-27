#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 1e5 + 5;

int n, d, k, T, likes[N], idx;
vector<int> v[N];
bool f[N];

int main()
{
    scanf("%d%d%d", &n, &d, &k);
    int x, y;
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &x, &y);
        T = max(T, x);
        idx = max(idx, y);
        v[x].push_back(y);
    }
    for(int i = 0; i <= T; i++)
    {
        if(i >= d)
            for(auto j : v[i - d])
                likes[j]--;
        for(auto j : v[i])
            if(++likes[j] >= k)
                f[j] = 1;
    }
    for(int i = 0; i <= idx; i++)
    if(f[i])
        printf("%d\n", i);
    return 0;
}
