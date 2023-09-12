#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> PII;

const int N = 1005;

int w[N][N], n;
bool st[N][N];
int peaks, valleys;
PII q[N * N];

void bfs(int sx, int sy)
{
    bool is_peak = true, is_valley = true;
    int hh = 0, tt = 0;
    q[0] = {sx, sy};
    st[sx][sy] = 1;
    while(hh <= tt)
    {
        PII tmp = q[hh++];
        int nx = tmp.first, ny = tmp.second;
        for(int i = nx - 1; i <= nx + 1; i++)
         for(int j = ny - 1; j <= ny + 1; j++)
         {
            if(i == nx && j == ny) continue;
            if(i < 1 || i > n) continue;
            if(j < 1 || j > n) continue;
            if(w[i][j] != w[nx][ny])
            {
                if(w[i][j] > w[nx][ny]) is_peak = false;
                else is_valley = false;
                continue;
            }
            if(st[i][j]) continue;
            st[i][j] = true;
            q[++tt] = {i, j};
         }
    }
    if(is_valley) valleys++;
    if(is_peak) peaks++;
}

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
     for(int j = 1; j <= n; j++)
      scanf("%d", &w[i][j]);
    for(int i = 1; i <= n; i++)
     for(int j = 1; j <= n; j++)
      if(!st[i][j]) 
      {
        bfs(i, j);
      }
    printf("%d %d\n", peaks, valleys);
    return 0;
}