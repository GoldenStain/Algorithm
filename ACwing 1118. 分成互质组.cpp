#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int n;
const int N = 15;
int a[N], ans = 20;
int mygroups[N][N];
bool vis[N];
int gcd(int x, int y)
{
    return y ? gcd(y, x % y) : x;
}
bool check(int gn[], int targets, int gcnts)
{
    for (int i = 0; i < gcnts; i++)
        if (gcd(gn[i], targets) > 1)
            return 0;
    return 1;
}
void dfs(int groups, int cnt, int startf, int gcnts)
{

    if (groups >= ans)
        return;
    if (cnt == n)
    {
        ans = groups;
        return;
    }
    bool flag = 1;
    for (int i = startf; i < n; i++)
    {
        if (!vis[i] && check(mygroups[groups], a[i], gcnts))
        {

            flag = 0;
            vis[i] = 1;
            mygroups[groups][gcnts] = a[i];
            dfs(groups, cnt + 1, i + 1, gcnts + 1);
            vis[i] = 0;
            if (gcnts == 0)
                return;
        }
    }
    if (flag)
        dfs(groups + 1, cnt, 0, 0);
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    dfs(1, 0, 0, 0);
    cout << ans << endl;
    return 0;
}