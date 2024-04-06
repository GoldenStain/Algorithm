#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

const int N = 250002, M = 5e5 + 2, H = 17;
typedef pair<int, int> PII;
typedef long long LL;

int n, dis[N], depth[N], fa[N][H + 1];// 开始不小心把fa的声明写成了fa[N][H]，导致数组越界，fa数组初始化失败，卡了好久
vector<PII> ed[N], vrg[N]; // ed是真边，vrg是虚树中的边
int m, in_ts[N], out_ts[N], ts; // ts表示时间戳
LL dp[N];
bool flag[N];

void init_lca(int root)
{
    depth[0] = 0; depth[root] = 1;
    queue<int> q;
    q.push(root);
    while(q.size())
    {
        int u = q.front();
        q.pop();
        for(auto pi : ed[u])
        {
            int v = pi.first;
            if(!depth[v])
            {
                q.push(v);
                depth[v] = depth[u] + 1;
                fa[v][0] = u;
                for(int k = 1; k <= H; k++)
                    fa[v][k] = fa[fa[v][k - 1]][k - 1];
            }
        }
    }
}

int get_lca(int a, int b)
{
    if(depth[a] < depth[b]) swap(a, b);
    for(int k = H; k >= 0; k--)
        if(depth[fa[a][k]] >= depth[b])
            a = fa[a][k];
    if(a == b)
        return a;
    for(int k = H; k >= 0; k--)
        if(fa[a][k] != fa[b][k])
            a = fa[a][k], b = fa[b][k];
    return fa[a][0];
}

void init(int u, int fa) //初始化距离数组
{
    in_ts[u] = ++ts;
    for(auto pi : ed[u])
    {
        int v = pi.first, dist = pi.second;
        if(v == fa)
            continue;
        // 一开始写成了min(dis[v], dist);卡了好久
        dis[v] = min(dis[u], dist);
        init(v, u);
    }
    out_ts[u] = ts;
}

bool cmp(int u, int v)
{
    return in_ts[u] < in_ts[v];
}

bool is_son(int u, int v)
{
    return in_ts[u] >= in_ts[v] && out_ts[u] <= out_ts[v];
}

void build(vector<int> &q, int Size)
{
    // puts("build");
    sort(q.begin(), q.end(), cmp);
    for(int i = 0; i < Size; i++)
        q.push_back(get_lca(q[i], q[i + 1]));
    sort(q.begin(), q.end(), cmp);
    q.erase(unique(q.begin(), q.end()), q.end());
    vector<int> st;
    for(auto u : q)
    {
        // puts("u from q");
        while(!st.empty() && !is_son(u, st.back()))
            st.pop_back();
        // 如果栈里还有点，就说明他们在虚树中的同一条链上
        if(!st.empty())
        {
            vrg[st.back()].push_back({u, dis[u]});
        }
        // 注意这句话不能写在if里面，只要我们还没有完成整个处理过程，就必须把遇到的每一个点入队
        st.push_back(u);
    }
}

void dp_dfs(int u)
{
    // puts("dp_dfs");
    dp[u] = 0;
    for(auto pi : vrg[u])
    {
        int v = pi.first, dist = pi.second;
        dp_dfs(v);
        if(flag[v])
            dp[u] += dist;
        else
            dp[u] += min(dp[v], (LL)dist);
    }
}

int main()
{
    scanf("%d", &n);
    int k;
    // dis[1]不用设置为0
    memset(dis, 0x3f, sizeof(dis));
    for(int i = 1; i < n; i++)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        ed[a].push_back(make_pair(b, w));
        ed[b].push_back(make_pair(a, w));
    }
    init(1, 0);
    init_lca(1);
    /* for(int i = 1; i <= n; i++)
        printf("%d ", depth[i]);
      puts("");
    printf("%d\n%d\n", get_lca(2, 5), dis[9]); */
    // exit(0);

    int tmp;

    scanf("%d", &m);
    while(m--)
    {
        scanf("%d", &k);
        vector<int> be_important;// 一开始直接开固定大小的vector，导致后来push_back lca时出错
        be_important.push_back(1);
        for(int i = 1; i <= k; i++)
        {
            scanf("%d", &tmp);
            be_important.push_back(tmp);
            flag[tmp] = true;
        }
        build(be_important, k);
        dp_dfs(1);
        printf("%lld\n", dp[1]);
        // 清空虚边
        for(auto t : be_important)
        {
            vrg[t].clear();
            flag[t] = 0;
        }
    }
    return 0;
}