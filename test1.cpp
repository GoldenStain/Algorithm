#include <bits/stdc++.h>
using namespace std;

struct EdgeElement{
    int y, ne;
};

struct EdgeElement edges[150];

int idx, h[10];

void add(int a, int b)
{
    edges[++idx].y = b;
    edges[idx].ne = h[a];
    h[a] = idx;
}

void connectPoints(int a, int b)
{
    add(a, b);
    add(b, a);
}

// a=1,b=2,c=3,d=4,e=5,f=6,g=7

int dis[15];

void dfs(int u)
{
    for(int i = h[u]; i; i = edges[i].ne)
    {
        int j = edges[i].y;
        if(dis[j]) continue;
        dis[j] = dis[u] + 1;
        dfs(j);
    }
}

bool check(int st)
{
    memset(dis, 0, sizeof(dis));
    for(int i = 0; i < 7; i++)
    {
        if((st >> i) & 1 == 0) continue;
        dis[i+1] = 1;
        dfs(i+1);
        break;
    }
    int Max = -1, Min = 10, cnt = 0;
    for(int i = 0; i < 7; i++)
    {
        if((st >> i) & 1 == 0) continue;
        cnt++;
        Max = max(Max, dis[i+1]);
        Min = min(Min, dis[i+1]);
    }
    cout << st << endl;
    cout << Max <<" "<< Min <<" "<< cnt << endl;
    if(Max - Min == cnt - 1)
        return 1;
    return 0;
}

int main()
{
    connectPoints(1, 2);
    connectPoints(1, 6);
    connectPoints(6, 7);
    connectPoints(2, 7);
    connectPoints(7, 5);
    connectPoints(7, 3);
    connectPoints(5, 4);
    connectPoints(3, 4);
    int ans = 0;
    for(int i = 0; i < (1 << 7); i++)
        if(check(i))
            ans++;
    cout << ans;
    return 0;
}