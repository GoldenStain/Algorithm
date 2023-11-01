#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
typedef pair<int,int> PII;
const int N=105,M=10110;
int n,l[N],Limit;
int h[N],ne[M],e[M],w[M],idx;
inline void add(int a,int b,int c)
{
    ne[++idx]=h[a];
    w[idx]=c;
    e[idx]=b;
    h[a]=idx;
}
int l_max=0,l_min=1000;
int dist[N];
bool vis[N];
void Dijkstra(int st,int ed)
{
    memset(vis,0,sizeof(vis));
    memset(dist,0x3f,sizeof(dist));
    dist[0]=0;dist[1]=w[1];
    priority_queue<PII,vector<PII>,greater<PII>> q;
    q.push({0,0});
    while(!q.empty())
    {
        auto tmp=q.top();
        q.pop();
        if(vis[tmp.second]) continue;
        int id=tmp.second;
        vis[id]=1;
        for(int i=h[id];i;i=ne[i])
        {
            int j=e[i];
            if(l[j]<st||l[j]>ed) continue;
            int D=dist[id]+w[i];
            if(D<dist[j])
            {
                dist[j]=D;
                q.push({dist[j],j});
            }
        }
    }
}
int main()
{
    scanf("%d%d",&Limit,&n);
    for(int i=1;i<=n;i++)
    {
        int val,cnt;
        scanf("%d%d%d",&val,&l[i],&cnt);
        l_max=max(l_max,l[i]);
        l_min=min(l_min,l[i]);
        add(0,i,val);
        int t,v_n;
        for(int j=1;j<=cnt;j++)
        {
            scanf("%d%d",&t,&v_n);
            add(t,i,v_n);
        }
    }
    int ans=w[1];
#ifdef DEBUG
    printf("%d\n",w[1]);
#endif
    for(int st=l_min;st<=l_max;st++)
    {
        int ed=st+Limit;
        Dijkstra(st,ed);
#ifdef DEBUG
    printf("tmp ans : %d\n",dist[1]);
#endif
        ans=min(ans,dist[1]);
    }
    printf("%d\n",ans);
    system("pause");
    return 0;
}