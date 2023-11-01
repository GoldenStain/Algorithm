#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int N = 105;

int n, m, f[N][N], ans;

int main()
{
    cin >> n >> m;
    memset(f, 0x3f, sizeof f);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        f[a][b] = f[b][a] = min(f[a][b], c);
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
    for (int i = 2; i <= n; i++)
        if (f[1][i] == 0x3f3f3f3f)
        {
            ans = -1;
            break;
        }
        else
            ans = max(ans, f[1][i]);
    cout << ans << endl;
    system("pause");
    return 0;
}