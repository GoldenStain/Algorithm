#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> PII;

const int N = 1005;
char g[N][N];
int n, m, dist[N][N];

void bfs() {
    queue<PII> q;
    memset(dist, -1, sizeof dist);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == '1') {
                dist[i][j] = 0;
                q.push({i, j});
            }
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    while (!q.empty()) {
        PII head = q.front();
        q.pop();
        int x = head.first, y = head.second;
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if (dist[nx][ny] != -1 || nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;
            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) scanf("%s", g[i]);
    bfs();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) printf("%d ", dist[i][j]);
        puts("");
    }
    return 0;
}