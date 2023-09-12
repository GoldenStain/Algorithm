#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <stack>
#include <vector>
#define x first
#define y second 
using namespace std;
typedef pair <int, int> PII;

const int N = 1005;
int n;
bool g[N][N];
int dist[N][N];
PII q[N * N], Pre[N][N];

void bfs(int x, int y)
{
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    memset(dist, -1, sizeof dist);
    int hh = 0, tt = 0;
    q[0] = {x, y};
    dist[x][y] = 0;
    while(hh <= tt)
    {
        PII tmp = q[hh++];
        int sx = tmp.first, sy = tmp.second;
        for(int i = 0; i < 4; i++)
        {
            int tx = sx + dx[i], ty = sy + dy[i];
            if(g[tx][ty]) continue;
            if(tx < 0 || tx >= n || ty < 0 || ty >= n || dist[tx][ty] != -1) continue;
            dist[tx][ty] = dist[sx][sy] + 1;
            Pre[tx][ty] = tmp;
            q[++tt] = {tx, ty};
        }
    } 
}

int main()
{
    cin >> n;
    for(int i = 0; i < n; i++) 
     for(int j = 0; j < n; j++)
      cin >> g[i][j];
    bfs(n - 1, n - 1);
    PII end = {0, 0};
    while(true)
    {
        cout << end.x << ' ' << end.y << endl;
        if(end.x == n - 1 && end.y == n - 1) break;
        end = Pre[end.x][end.y];
    }
    return 0;
}