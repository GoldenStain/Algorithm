#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 2e6 + 10;
typedef long long LL;
typedef pair<LL, int> PLI;

int A, B, C, m, num, now, opidx[N]; // now记录当前是第几次操作,opidx记录每个点的最后一次操作处于第几次
vector<PLI> ops[N/2]; // 记录操作序列
LL nhp[N];

int xytok(int x, int y, int z)
{
    return ((x - 1) * B + (y - 1)) * C + z; 
}

void op_push(int k, int h)
{
    //printf("op push : %d, %d\n", k, h);
    if(ops[k].empty())
    {
        ops[k].push_back({(LL)h, now});
        opidx[k] = now;
        return ;
    }
    if(opidx[k] != now)
    {
       ops[k].push_back({(LL)h, now});
    }
    else
    {
        ops[k].back().first += (LL)h;
    }
    opidx[k] = now;
    //nhp[k] += (LL)h;
}

void Operate(int x1,int y1, int z1, int x2, int y2, int z2, int h)
{
    op_push(xytok(x1, y1, z1), h);
    op_push(xytok(x2 + 1, y1, z1), -h);
    op_push(xytok(x1, y1, z2 + 1), -h);
    op_push(xytok(x2 + 1, y1, z2 + 1), h);

    op_push(xytok(x1, y2 + 1, z1), -h);
    op_push(xytok(x2 + 1, y2 + 1, z1), h);
    op_push(xytok(x1, y2 + 1, z2 + 1), h);
    op_push(xytok(x2 + 1, y2 + 1, z2 + 1), -h);
}

void add(LL h[], int x, int y, int z)
{
    h[xytok(x, y, z)] += h[xytok(x - 1, y, z)] + h[xytok(x, y - 1, z)] + h[xytok(x, y, z - 1)] 
                  - h[xytok(x, y - 1, z - 1)] - h[xytok(x - 1, y, z - 1)] - h[xytok(x - 1, y - 1, z)]
                  + h[xytok(x - 1, y - 1, z - 1)];
}

int find(vector<PLI> &v, int x)
{
    int l = 0, r = v.size() - 1;
    while(l < r)
    {
        int mid = l + r + 1 >> 1;
        if(v[mid].second <= x) l = mid;
        else r = mid - 1;
    }
    return l;
}

bool check(int x)
{
    for(int i = 1; i <= num; i++)
    {
        int pos = find(ops[i], x);
        nhp[i] = ops[i][pos].first;
    }
    /*for(int i = 1; i <= num; i++)
        printf("%d ", nhp[i]);
    puts("");*/
    for(int i = 1, cnt = 1; i <= A; i++)
        for(int j = 1; j <= B; j++)
            for(int k = 1; k <= C; k++, cnt++)
            {
                add(nhp, i, j, k);
                if(nhp[cnt] < 0ll)
                {
                    //printf("destroyed at (%d, %d, %d, %d)\n", i, j, k, x);
                    return true;
                }
            }
    return false;
}

int search()
{
    int l = 1, r = m;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main()
{
    int tmp;
    scanf("%d%d%d%d", &A, &B, &C, &m);
    for (int i = 1; i <= A; i++)
        for (int j = 1; j <= B; j++)
            for (int k = 1; k <= C; k++, num++)
            {
                scanf("%d", &tmp);
                // 把初始化也看成一次操作，就不需要特判了
                Operate(i, j, k, i, j, k, tmp);
            }
    now++;
    int x1, y1, z1, x2, y2, z2, h;
    for (int i = 1; i <= m; i++, now++)
    {
        scanf("%d%d%d%d%d%d%d", &x1, &x2, &y1, &y2, &z1, &z2, &h);
        Operate(x1, y1, z1, x2, y2, z2, -h);
    }
    /*printf("size:\n");
    for(int i = 1; i <= num; i++)
        printf("%d ", ops[i].size());
    puts("");*/
    for(int i = 1; i <= num; i++)
            for(int j = 1; j < ops[i].size(); j++)
                ops[i][j].first += ops[i][j - 1].first;
    /*check(2);
    for(int i = 1; i <= num; i++)
        printf("%lld ", nhp[i]);
    puts("");
    exit(0);*/
    printf("%d\n", search());
    return 0;
}