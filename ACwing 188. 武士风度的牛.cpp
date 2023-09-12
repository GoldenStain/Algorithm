#include <iostream>
#include <utility>
#define x first
#define y second
using namespace std;
typedef pair<int, int> PII;

const int N = 155;
char g[N][N];
bool st[N][N];
int n, m, dist;
PII q[N * N];

int bfs(int x, int y)
{
    int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
    int hh = 0, tt = 0;
    q[0] = {x, y};
    st[x][y] = 1;
    while (hh <= tt)
    {
        PII tmp = q[hh++];
        int sx = tmp.x, sy = tmp.y;
        for (int i = 0; i <= 8; i++)
        {
            int tx = sx + dx[i], ty = sy + dy[i];
            if (tx < 0 || tx >= n || ty < 0 || ty >= m)
                continue;
            if (st[tx][ty] || g[tx][ty] == '*')
                continue;
            dist++;
            if (g[tx][ty] == 'H')
                return dist;
            q[++tt] = {tx, ty};
            st[tx][ty] = 1;
        }
    }
    return -1;
}

int main()
{
    cin >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> g[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == 'K')
                cout << bfs(i, j) << endl;
    return 0;
}