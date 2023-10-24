#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#define x first
#define y second
using namespace std;
typedef pair<int, int> PII;
typedef pair<int, PII> PiI;

const int N = 1005, M = 1e4 + 5;

int n, s, t, m, k;
int idx, h[N], ne[M << 1], val[M << 1], dist[N], e[M << 1];
int rh[N];

inline void add(int h[], int a,int b, int c)
{
    ne[++idx] = h[a];
    h[a] = idx;
    val[idx] = c;
    e[idx] = b;
}

bool vis[N];

inline void init(int s, int t)
{
    priority_queue<PII, vector<PII>, greater<PII> > q;
    memset(dist, 0x3f, sizeof dist);
    q.push({0, s});
    dist[s] = 0;
    while(!q.empty())
    {
        auto t = q.top();
        int dis = t.x, num = t.y;
        q.pop();
        if(vis[num]) continue;
        vis[num] = 1;
        for(int i = rh[num]; i; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > dis + val[i])
            {
                dist[j] = dis + val[i];
                q.push({dist[j], j});
            }
        }
    }
}

int cnt[N];

int k_solve(int s, int t, int k)
{
    priority_queue<PII, vector<PII>, greater<PII> > q;
    q.push({dist[s], s});
    while(!q.empty())
    {
        PII tmp = q.top();
        q.pop();
        int num = tmp.y;
        int ans = tmp.x - dist[num];
        cnt[num]++;
        if(cnt[t] == k) return ans;
        if(cnt[num] > k) continue;
        for(int i = h[num]; i; i = ne[i])
        {
            int j = e[i];
            q.push({ans + val[i] + dist[j], j});
        }
    }
    return -1;
}

int main()
{
    scanf("%d%d", &n, &m);
    int a, b, c;
    for(int i = 1; i <= m; i++) 
    {
        scanf("%d%d%d", &a, &b, &c);
        add(h, a, b, c);
        add(rh, b, a, c);
    }
    scanf("%d%d%d", &s, &t, &k);
    if(s == t) k++;
    init(t, s);
    #ifdef DEBUG
    printf("%d\n", dist[1]);
    #endif
    int ans = k_solve(s, t, k);
    printf("%d\n", ans);
    return 0;
}