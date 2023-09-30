#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <deque>
typedef pair<int, int> PII;

using namespace std;

const int N = 505;

int T, n, m, dist[N][N];
char g[N][N];
bool vis[N][N];

void bfs()
{
    deque<PII> q;
    q.push_front(make_pair(0, 0));
    dist[0][0] = 0;
    int dx[] = {-1, -1, 1, 1}, dy[] = {-1, 1, 1, -1};
    int ix[] = {-1, -1, 0, 0}, iy[] = {-1, 0, 0, -1};
    char mv[] = "\\/\\/";
    while(!q.empty())
    {
        PII tmp = q.front();
        q.pop_front();
        int x = tmp.first, y = tmp.second;
        if(vis[x][y]) continue;
        vis[x][y] = 1;
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            int fx = x + ix[i], fy = y + iy[i];
            int d = g[fx][fy] != mv[i];
            if(d + dist[x][y] < dist[nx][ny]) 
            {
                dist[nx][ny] = dist[x][y] + d;
                if(d) q.push_back(make_pair(nx, ny));
                else q.push_front(make_pair(nx, ny));
            }
        }
    }
}

int main()
{
    scanf("%d", T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) 
         scanf("%s", g[i]);
        if(n + m & 1) 
        {
            puts("NO SOLUTION");
            continue;
        }
        memset(dist, 0x3f, sizeof dist);
        memset(vis, 0, sizeof(vis));
        bfs();
        printf("%d\n", dist[n - 1][m - 1]);
    }
    return 0;
}