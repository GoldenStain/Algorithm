#include <iostream>
#include <cstring>
using namespace std;
const int N = 25;
char g[N][N];
int n, m;
bool vis[N][N];
//先列后行
int sx, sy;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int ans;
void dfs(int x, int y, int step)
{
	ans = max(ans, step);
	vis[x][y] = 1;
	for(int i = 0; i < 4; i++)
	{
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if(g[nx][ny] == '#') continue;
		if(vis[nx][ny]) continue;
		dfs(nx, ny, step + 1);
	}
}
int main()
{
	while(cin >> m >> n)
	{
		ans = 0;
		memset(vis, 0, sizeof(vis));
		if(!m && !n) break;
		for(int i = 0; i < n; i++)
		 for(int j = 0; j < m; j++)
		{
			cin >> g[i][j];
			if(g[i][j] == '@') 
			{
				sx = i;
				sy = j;
			}
		}
		dfs(sx, sy, 1);
		cout << ans << "\n";
	}
	return 0;
}