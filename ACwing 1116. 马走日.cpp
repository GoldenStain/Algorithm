#include <iostream>
#include <algorithm>
using namespace std;

const int N = 15;

int sx, sy, n, m, t, ans;
bool vis[N][N];

int dx[] = {-2,-1,1,2,2,1,-1,-2},
    dy[] = {1,2,2,1,-1,-2,-2,-1};

void dfs(int sx, int sy, int cnt)
{
    if(cnt == n * m) 
    {
        ans++;
        return;
    }
    vis[sx][sy] = 1;
    for(int i = 0; i < 8; i++)
    {
        int nx = sx + dx[i];
        int ny = sy + dy[i];
        if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
        if(vis[nx][ny]) continue;
        dfs(nx, ny, cnt + 1);
    }
    vis[sx][sy] = 0;
}

int main()
{
    cin >> t;
    while(t--)
    {
        ans = 0;
        cin >> n >> m >> sx >> sy;
        dfs(sx, sy, 1);
        cout << ans << endl;
    }
    return 0;
}