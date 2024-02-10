#include<bits/stdc++.h>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

const int N = 2e6 + 10;
typedef long long LL;
typedef pair<LL, int> PLI;

int A, B, C, m, num = 1, now, op[N / 2][7]; // now记录当前是第几次操作,opidx记录每个点的最后一次操作处于第几次
LL hp[N], dmg[N];

int xytok(int x, int y, int z)
{
    return ((x - 1) * B + (y - 1)) * C + z;
}

void Operate(LL b[], int x1, int y1, int z1, int x2, int y2, int z2, LL h)
{
    b[xytok(x1, y1, z1)] += h; // 伤害为 负
    b[xytok(x1, y1, z2 + 1)] -= h;
    b[xytok(x1, y2 + 1, z1)] -= h;
    b[xytok(x1, y2 + 1, z2 + 1)] += h;
    b[xytok(x2 + 1, y1, z1)] -= h;
    b[xytok(x2 + 1, y1, z2 + 1)] += h;
    b[xytok(x2 + 1, y2 + 1, z1)] += h;
    b[xytok(x2 + 1, y2 + 1, z2 + 1)] -= h;
}

void add(LL b[], int i, int j, int k)
{
        b[xytok(i, j, k)]+=
		b[xytok(i-1, j, k)]+
		b[xytok(i, j-1, k)]+
		b[xytok(i, j, k-1)]-	
		b[xytok(i-1, j-1, k)]-	
		b[xytok(i-1, j, k-1)]-	
		b[xytok(i, j-1, k-1)]+	
		b[xytok(i-1, j-1, k-1)];			    
}

bool check(int x)
{
    memset(dmg, 0, sizeof dmg);
    for (int i = 1; i <= x; i++) // x1,x2,y1,y2,z1,z2,h
    {
        int x1 = op[i][0], x2 = op[i][1], y1 = op[i][2], y2 = op[i][3], z1 = op[i][4], z2 = op[i][5], h = op[i][6];
        Operate(dmg, x1, y1, z1, x2, y2, z2, (LL)h);
    }
    for (int i = 1, cnt = 1; i <= A; i++)
        for (int j = 1; j <= B; j++)
            for (int k = 1; k <= C; k++, cnt++)
            {
                add(dmg, i, j, k);
                if (dmg[cnt] > hp[cnt])
                    return 1;
            }
    return 0;
}

int search()
{
    int l = 1, r = m;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    return r;
}

int main()
{
    int tmp;
    scanf("%d%d%d%d", &A, &B, &C, &m);
    for (int i = 1; i <= A; i++)
        for (int j = 1; j <= B; j++)
            for (int k = 1; k <= C; k++, num++)
            {
                scanf("%lld", &hp[num]);
                // Operate(bp, i, j, k, i, j, k, hp[num]);
            }
    num--;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < 7; j++)
            scanf("%d", &op[i][j]);
    }
    printf("%d\n", search());
    return 0;
}