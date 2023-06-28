#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
 
const int N = 2e5 + 5;
 
int n, col[N], id[N], tot, ans;
vector <int> g[N];
 
struct Mystruct
{
    map<int, int> cnt;
    vector<int> list;
    void add(int u)
    {
        cnt[col[u]] ++;
        list.push_back(u);
    }
    int size()
    {
        return list.size();
    }
} sub[N];
 
void dfs(int u,int fa)
{
    int max_id = -1, max_son = 0;
    id[u] = ++ tot;
    for(int v : g[u])
    {
        if(v == fa)
            continue;
        dfs(v, u);
        if(sub[id[v]].size() > max_son) 
        {
            max_son = sub[id[v]].size();
            max_id = v;
        }
    }
    if(max_id != -1) 
        id[u] = id[max_id];
    for(int v : g[u])
    {
        if(v == fa || v == max_id) 
            continue;
        for(int w : sub[id[v]].list)
            sub[id[u]].add(w);
    }
    sub[id[u]].add(u);
    int times = 0, standard_v = 0;
    bool flag = 1;
    for(const auto& pair : sub[id[u]].cnt)
    {
        if(times == 0) standard_v = pair.second;
        else if(standard_v != pair.second) 
        {
            flag = 0;
            break;
        }
        times = 1;
    }
    if(flag) ans ++;
}   
 
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i ++)
    {
        int x;
        scanf("%d%d", &col[i], &x);
        if(x) g[x].push_back(i);
    }
    dfs(1, 0);
    printf("%d\n", ans);
    system("pause");
    return 0;
}