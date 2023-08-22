#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

const int N = 1005;

int a, b, n, g[N][N], res = 1e9, hh ,tt, q[N];
int row_max[N][N], row_min[N][N], line_max[N], line_min[N];

void get_max(int pattern[], int target[])
{
    hh = 0; tt = -1;
    for(int i = 1; i <= b; i++)
    {
        if(hh <= tt && q[hh] <= i - n) hh++;
        while(hh <= tt && pattern[q[tt]] <= pattern[i]) tt--;
        q[++tt] = i;
        target[i] = pattern[q[hh]];
    }
}

void get_min(int pattern[], int target[])
{
    hh = 0; tt = -1;
    for(int i = 1; i <= b; i++)
    {
        if(hh <= tt && q[hh] <= i - n) hh++;
        while(hh <= tt && pattern[q[tt]] >= pattern[i]) tt--;
        q[++tt] = i;
        target[i] = pattern[q[hh]];
    }
}

int main()
{
    scanf("%d%d%d", &a, &b, &n);
    for(int i = 1; i <= a; i++)
     for(int j = 1; j <= b; j++)
      scanf("%d", &g[i][j]);
    for(int i = 1; i <= a; i++)
    {
        get_max(g[i], row_max[i]);
        get_min(g[i], row_min[i]);
    }
    for(int i = n; i <= b; i++)
    {
        hh = 0; tt = -1;
        int mh=0, mt = -1;
        for(int j = 1; j <= a; j++)
        {
            //printf("row:%d ", j);
            //先求最大值
            if(hh <= tt && line_max[hh] <= j - n) hh ++;
            while(hh <= tt && row_max[j][i] >= row_max[line_max[tt]][i]) tt--;
            line_max[++tt] = j;
            //求最小值
            if(mh <= mt && line_min[mh] <= j - n) mh ++;
            while(mh <= mt && row_min[j][i] <= row_min[line_min[mt]][i]) mt--;
            line_min[++mt] = j;
            //printf("max:%d, min: %d\n",row_max[line_max[hh]][i], row_min[line_min[mh]][i]);
            if(j >= n) res = min(res, row_max[line_max[hh]][i] - row_min[line_min[mh]][i]);
        }
    }
    printf("%d", res);
    return 0;
}