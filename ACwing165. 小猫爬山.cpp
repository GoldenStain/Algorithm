#include <iostream>
#include <algorithm>
#include <stdlib.h>
using namespace std;

const int N = 20, INF = 1e9;
int n, m, ans = INF;
int a[N], w[N];

void dfs(int Now, int Cars)
{
    if (Cars >= ans)
        return;
    if (Now == n + 1)
    {
        ans = Cars;
        return;
    }
    for (int i = 1; i <= Cars; i++)
        if (w[i] + a[Now] <= m)
        {
            w[i] += a[Now];
            dfs(Now + 1, Cars);
            w[i] -= a[Now];
        }
    w[Cars + 1] = a[Now];
    dfs(Now + 1, Cars + 1);
    w[Cars + 1] = 0;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    reverse(a + 1, a + n + 1);
    dfs(1, 0);
    cout << ans << endl;
    return 0;
}