#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>
#define R(x) x = read()
using namespace std;
typedef pair<int, int> PII;

const int N = 2510, M = 12410;

int n, m, s, t;
int h[N], ne[M], e[M], w[M], idx;
int dist[N];
bool vis[N];

inline int read()
{
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')
        ch = getchar();
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

inline void add(int a, int b, int c)
{
    ne[++idx] = h[a];
    e[idx] = b;
    w[idx] = c;
    h[a] = idx;
}

void Dijkstra(int s, int t)
{
    priority_queue<PII, vector<PII>, greater<PII>> q;
    memset(dist, 0x3f, sizeof dist);
    dist[s] = 0;
    q.push({0, s});
    while(!q.empty())
    {
        auto tmp = q.top();
        q.pop();
        int DisNow = tmp.first, id = tmp.second;
        if(vis[id]) continue;
        vis[id] = 1;
        for(int i = h[id]; i; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > DisNow + w[i])
            {
                dist[j] = DisNow + w[i];
                q.push({dist[j], j});
            }
        }
    }
}

    int main()
{
    R(n);
    R(m);
    R(s);
    R(t);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c;
        R(a);
        R(b);
        R(c);
        add(a, b, c);
        add(b, a, c);
    }
    Dijkstra(s, t);
    printf("%d\n", dist[t]);
    system("pause");
    return 0;
}