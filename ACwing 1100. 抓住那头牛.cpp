#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int N = 1e5 + 5;

int n, k, dist[N], q[N];
bool st[N];

void bfs(int s)
{
    int hh = 0, tt = 0;
    q[0] = s;
    while (hh <= tt)
    {
        int tmp = q[hh];
        int Dis = dist[q[hh++]];
        if (tmp == k)
            return;
        if (tmp + 1 < N && !st[tmp + 1])
        {
            q[++tt] = tmp + 1;
            st[tmp + 1] = 1;
            dist[tmp + 1] = Dis + 1;
        }
        if (tmp - 1 >= 0 && !st[tmp - 1])
        {
            q[++tt] = tmp - 1;
            st[tmp - 1] = 1;
            dist[tmp - 1] = Dis + 1;    
        }
        if (tmp * 2 < N && !st[tmp << 1])
        {
            q[++tt] = tmp << 1;
            st[tmp << 1] = 1;
            dist[tmp << 1] = Dis + 1;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &k);
    bfs(n);
    printf("%d\n", dist[k]);
    return 0;
}