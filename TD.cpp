#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <cmath>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

typedef long long LL;
const int N = 1e5 + 5;

struct StrForPos{
    int x, y;
    bool operator < (const StrForPos &t) const
    {
        int s = x + y, ts = t.x + t.y;
        if(s != ts)
            return s < ts;
        return x < t.x;
    }
}p[N];

int n;
LL ans;

int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d%d", &p[i].x, &p[i].y);
    }
    sort(p + 1, p + n + 1);
    /*for(int i = 1; i <= n; i++)
        cout << p[i].x << " " << p[i].y << endl;*/
    p[0] = p[1];
    int dx = -1, dy = -1, st = 0, ed = 0;
    bool flag = false;
    for(int i = 1; i <= n; i++)
    {
       dx = p[i].x - p[i - 1].x;
       dy = p[i].y - p[i - 1].y;
       if(!flag && abs(dx) <= 1 && abs(dy) <= 1)
       {
        flag = true;
        st = i;
       }       
       if(flag && (abs(dx) > 1 || abs(dy) > 1))
       {
        ed = i - 1;
        flag = false;
        printf("%d %d %d %d\n", p[ed].x, p[ed].y, p[st].x, p[st].y);
        ans += (LL)(p[ed].y - p[st].y + 1) * (p[ed].x - p[st].x + 1);
       }
    }
    printf("%lld\n", ans);
    return 0;
}
