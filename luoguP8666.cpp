#include<bits/stdc++.h>

using namespace std;
typedef long long  LL;
const int N = 2000010;

int A, B, C, m;// 层，行，列， 攻击轮数
LL s[N], b[N], bp[N];// 生命值， 差分数组，备份差分数组
int op[N / 2][7];// 攻击范围及伤害

// 差分数组八个方向偏移量
int d[8][4] = 
{
    {0, 0, 0,  1},
    {0, 0, 1, -1},
    {0, 1, 0, -1},
    {0, 1, 1,  1},
    {1, 0, 0, -1},
    {1, 0, 1,  1},
    {1, 1, 0,  1},
    {1, 1, 1, -1},
};

int get(int i, int j, int k)// 压维映射函数
{
    return ((i-1) * B + j-1) * C + k;
}
bool check(int mid)
{
    memcpy(b, bp, sizeof b);
    for(int i = 1; i <= mid; i ++ )
    {
        int x1 = op[i][0], x2 = op[i][1], y1 = op[i][2], y2  = op[i][3], z1 = op[i][4], z2 = op[i][5], h = op[i][6];
        b[get(x1,     y1,         z1)] += -h; // 伤害为 负
        b[get(x1,     y1,     z2 + 1)] -= -h;
        b[get(x1,     y2 + 1,     z1)] -= -h;
        b[get(x1,     y2 + 1, z2 + 1)] += -h;
        b[get(x2 + 1, y1,         z1)] -= -h;
        b[get(x2 + 1, y1,     z2 + 1)] += -h;
        b[get(x2 + 1, y2 + 1,     z1)] += -h;
        b[get(x2 + 1, y2 + 1, z2 + 1)] -= -h;
        
    }
   
    /* 求前缀和

     s[i][j][k] = s[i-1][j][k]+s[i][j-1][k]+s[i][j][k-1]-s[i-1][j-1][k]-s[i-1][j][k-1]-s[i][j-1][k-1]+s[i-1][j-1][k-1]+b[i][j][k]

     */
    memset(s, 0, sizeof s);
    for(int i = 1; i <= A; i ++ )
        for(int j = 1; j <= B; j ++ )
            for(int k = 1; k <= C; k ++ )
            {
                s[get(i, j ,k)] = b[get(i, j, k)];
                for(int u = 1; u < 8; u ++ )
                {
                    int x = i - d[u][0], y = j - d[u][1], z = k - d[u][2], t = d[u][3];
                    s[get(i, j, k)] -= s[get(x, y, z)] * t;

                }
                if(s[get(i, j, k)] < 0) return true;
            }

    return false;

}
int main()
{

    scanf("%d%d%d%d", &A, &B, &C, &m);

    // 生命值读入
    for(int i = 1; i <= A; i ++ )
        for(int j = 1; j <= B; j ++ )
            for(int k = 1; k <= C; k ++ )
                scanf("%lld", &s[get(i, j, k)]);

    // 求差分数组 b[]
    for(int i = 1; i <= A; i ++ )
        for(int j = 1; j <= B; j ++ )
            for(int k = 1; k <= C; k ++)
                for(int u = 0; u < 8; u ++ )
                {
                    int x = i - d[u][0], y = j - d[u][1], z = k - d[u][2], t = d[u][3];
                    bp[get(i, j, k)] += s[get(x, y, z)] * t;


                }

    // 读入覆盖范围，攻击伤害 
    for(int i = 1; i <= m; i ++ )
        for(int j = 0; j < 7; j ++ )
            scanf("%d", &op[i][j]);
        
    // 二分
    int l = 1, r = m;
    while(l < r)
    {
        int mid = l + r >> 1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }

    printf("%d\n", r);


    return 0;
    
}
