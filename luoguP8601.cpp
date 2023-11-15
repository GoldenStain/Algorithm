#include <bits/stdc++.h>
#define int long long
using namespace std;
const int inf = 1e16;
int a[15][15], n, m, visit[15][15]; // a[i][j]代表第 i,j 的数值 ，visit[i][j]代表 i,j 有没有已经算过了
int xxx[5] = {0, 1, -1, 0, 0};
int yyy[5] = {0, 0, 0, -1, 1}; // 移动
int ANS = inf;                 // 全局变量记录答案，因为求最小值就要出到最大
int tot;                       // 总和
bool visit1[15][15];           // 判断连通块访问
void Sou(int x, int y)
{
    visit1[x][y] = 1;
    for (int i = 1; i <= 4; i++) // 朝4个方向前进
    {
        int xx = x + xxx[i], yy = y + yyy[i]; // 当前所在位置
        if (xx < 1 || xx > n || yy < 1 || yy > m)
            continue;
        if (!visit1[xx][yy] && !visit[xx][yy])
            Sou(xx, yy); // 继续搜索
    }
}
bool check()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            visit1[i][j] = 0;
    int C = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            if (visit1[i][j] || visit[i][j])
                continue; // 已经搜到了
            if (C)
                return false;
            Sou(i, j); // 搜索，如果一次搜完，就代表ok,两个，否则有>=3个连通块
            C++;
        }
    if (!C)
        return false;
    return true;
}
void dfs(int x, int y, int ans, int sum) // 如思路里所说
{
    visit[x][y] = 1;
    if (ans >= ANS)
        return;                    // 优化
    if (sum * 2 == tot && check()) // 判断符合条件
    {
        ANS = min(ANS, ans);
        return; // 记录
    }
    for (int i = 1; i <= 4; i++) // 朝4个方向前进
    {
        int xx = x + xxx[i], yy = y + yyy[i]; // 当前所在位置
        if (xx < 1 || xx > n || yy < 1 || yy > m)
            continue; // 超越边界或者已经访问过，下次循环,其中sum+a[xx][yy]>tot/2为剪枝，不用继续搜索
        if (!visit[xx][yy])
            if (sum + a[xx][yy] > tot / 2)
                continue;
            else
                dfs(xx, yy, ans + 1, sum + a[xx][yy]); // 更新,真玄学，我把visit放这里67并且hackTLE,放到头上就AC了，欢迎讨论啊
    }
    visit[x][y] = 0;
}
int sx, sy;
signed main()
{
    cin.tie(0);
    cout.tie(0); // 优化
    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            cin >> a[i][j], tot += a[i][j]; // 输入+记录总和
    if (tot % 2 == 1)
    {
        puts("0");
        return 0; // 特判
    }

    //-----------
    // 被hack部分
    for (int i = 1; i <= n; i++) // 枚举
        for (int j = 1; j <= m; j++)
            if (ANS == inf) // 还没有搜到
            {
                dfs(i, j, 1, a[i][j]);
                sx = i;
                sy = j;
            } // 从i,j搜索，已经有一个点，总和有i,j的值
            else
                break; // 搜到了！
    //------------
    if (ANS == inf) // 没有搜到方案，输出0
        puts("0");
    else
    {
        if(visit1[1][1]) ANS = n * m - ANS;
        cout << ANS << '\n'; // 输出
    }

    system("pause");
    return 0;
}