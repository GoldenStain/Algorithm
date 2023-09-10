#include <stdio.h>
#include <utility>
#include <stdlib.h>
using namespace std;
typedef pair<int, int> PII;

const int N = 1005;
char g[N][N];
int n,m,cnt;
bool flag[N][N];
PII q[N*N];
int dx[8] = {-1,-1,-1,1,1,1,0,0},
    dy[8] = {-1,0,1,-1,0,1,-1,1};

void bfs(int sx,int sy)
{
    int hh = 0, tt = 0;
    flag[sx][sy] = 1;
    q[hh] = {sx,sy};
    while(hh <= tt)
    {
        PII tmp = q[hh++];
        int tx = tmp.first, ty = tmp.second;
        for(int i = 0; i < 8; i++)
        {
            int nx = tx + dx[i], ny = ty + dy[i];
            if(nx < 0 || nx >= n || ny < 0 || ny >= m || flag[nx][ny] || g[nx][ny] != 'W') continue;
            flag[nx][ny] = 1;
            q[++tt]={nx,ny};
        }
    }
    cnt++;
}

int main()
{
    scanf("%d%d",&n, &m);
    for(int i = 0; i < n; i++)  
     scanf("%s",g[i]);
    for(int i = 0; i < n; i++)
     for(int j = 0; j < m; j++)
      if(!flag[i][j] && g[i][j] == 'W') bfs(i,j);
    printf("%d\n",cnt);
    return 0;
}