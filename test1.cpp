#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include <vector>
#define R register
using namespace std;
const int N = 1e4 + 5, M = 105, INF = 1e7;
int n, m, w[N];
inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}
int main()
{
    n = read();
    m = read();
    for (R int i = 1; i <= n; i++)
        w[i] = read();
    priority_queue<int, vector<int>, greater<int>> lq;
    for (R int i = 1; i <= m; i++)
    {
        lq.push(w[i]);
    }
    for (R int i = m + 1; i <= n; i++)
    {
        int now = lq.top();
        lq.pop();
        lq.push(now + w[i]);
    }
    int ans = -1;
    while (!lq.empty())
    {
        ans = max(ans, lq.top());
        lq.pop();
    }
    printf("%d", ans);
    return 0;
}