#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int, int> PII;

const int N = 25005, M = 50005, inf = 1e9;

int h[N], e[M * 3], w[M * 3], ne[M * 3], cnt, id[N], idnow;
int n, r, p, s;
bool flag[N], vis[N];
int dist[N], in_degree[N];
vector<int> vec[N];
queue<int> q_block;

inline void add(int a, int b, int c)
{
    e[++cnt] = b;
    w[cnt] = c;
    ne[cnt] = h[a];
    h[a] = cnt;
}

void dfs(int u,int mark_id)
{
    vec[mark_id].push_back(u);
    id[u] = mark_id;
    for(int i = h[u]; i; i = ne[i])
    {
        int j = e[i];
        if(!flag[j])
        {
            flag[j] = 1;
            dfs(j, mark_id);
        }
    }
}

void DJ(int u)
{
    priority_queue<PII, vector<PII>, greater<PII>> Q;
    for(auto i : vec[u])
        Q.push({dist[i], i});
    while(!Q.empty())
    {
        PII q_top = Q.top();
        Q.pop();
        int x = q_top.second;
        if(vis[x]) continue;
        vis[x] = 1;
        for(int i = h[x]; i; i = ne[i])
        {
            int j = e[i];
            if(id[j] == id[x])
            {
                if(dist[j] > dist[x] + w[i])
                {
                    dist[j] = dist[x] + w[i];
                    Q.push({dist[j], j});
                }
            }
            else
            {
                dist[j] = min(dist[j], dist[x] + w[i]);
                in_degree[id[j]]--;
                if(!in_degree[id[j]])
                {
                    q_block.push(id[j]);
                }
            }
        }
    }
}

void func()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    for(int i = 1; i <= idnow; i++)
    {
        if(!in_degree[i])
        {
            q_block.push(i);
        }
    }
    while(!q_block.empty())
    {
        int block_first = q_block.front();
        q_block.pop();
        DJ(block_first);
    }
}

int main()
{
    scanf("%d%d%d%d", &n, &r, &p, &s);
    for(int i = 1; i <= r; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        add(b, a, c);
    }
    for(int i = 1; i <= n; i++)
        if(!flag[i])
        {
            flag[i] = 1;
            idnow++;
            dfs(i, idnow);
        }
    for(int i = 1; i <= p; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        add(a, b, c);
        in_degree[id[b]]++;
    }
    func();
    for(int i = 1; i <= n; i++)
        if(dist[i] < inf)
            printf("%d\n", dist[i]);
        else
            puts("NO PATH");
    system("pause");
    return 0;
}
