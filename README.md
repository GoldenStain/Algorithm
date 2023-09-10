# Algorithm
算法题题解
some solutions to algorithm problems
## AcWing 1083. Windy数 
https://www.acwing.com/problem/content/1085/

**1** f[i][j]表示从最高位为第i位，且最高位填的数字是j的方案数。

**2** 这道题有前导零和无前导零的情况要分开处理，因为虽然013和13本质上都表示13这个数，但是按照我们这道题的DP初始化方式，013并不会被计入res当中，只有13会，因此我们需要将有前导零的情况特殊处理，以防止res偏小。

**3** 特殊处理时为什么要写成

*1*
```
for(int i = len - 1; i > 0; i --)
     for(int j = i != 1; j <= 9; j ++)
      res += f[i][j];
    return res;
```

而不是

*2*
```
for(int i = len - 1; i > 0; i --)
     for(int j = 1; j <= 9; j ++)
      res += f[i][j];
    return res;
```

因为我们在solve函数的开头有`if(!x) return 1;` 这是把0计入windy数的，倘若我们写成*2*那样，就会把0漏掉，虽然能避免错误地出现前导零，但还是会在最后造成答案错误。
## 1084. 数字游戏 II
https://www.acwing.com/problem/content/description/1086/

这道题整体上和数字游戏Ⅰ基本相同，本题中dp数组f[i][j][k]表示一共有i位的数字，最高位填j，各位数字之和模n为k时的方案数，整体逻辑框架与Windy数相同。

## 蓝桥杯2023 省赛 颜色平衡树
http://oj.ecustacm.cn/problem.php?id=2071
启发式合并模板题，启发式合并学习链接：https://zhuanlan.zhihu.com/p/560661911

## 蓝桥杯2023 省赛 买瓜
http://oj.ecustacm.cn/problem.php?id=2072
meet in the middle算法，洛谷题解链接：https://www.luogu.com.cn/problem/solution/P9234

## 蓝桥杯2023 省赛 异或和之和
https://www.luogu.com.cn/problem/P9236
经典题，洛谷题解链接：https://www.luogu.com.cn/problem/solution/P9236
w[i][j]表示在所有前缀和当中，第i位上j的个数，j只能取0或者1，注意在初始化w数组时，要把s[0]也算上，因为有从形式如[1,r]的区间存在。

## codeforces Educational Codeforces Round 151 (Rated for Div. 2) D. Rating System

https://codeforces.com/contest/1845/problem/D
首先通过前缀和求出前x个数的总和，通过题目可以想到k的取值为每场比赛过后的评分。通过逆向思维，想要求出最终的评分最大，则要求出这个k能够帮你提升评分的最大值。假设，则此后每一轮比赛过后能够提升评分的值为。
因此，假设当前进行到了第x场比赛，则能够提升评分的最大值为max{sum[0],sum[1]...sum[x-1]} - sum[x]。 所以，我们可以遍历一遍整个sum数组，同时维护当前序列x的最大前缀和max_sum和最大能够提升的评分max_point = max_sum - sum[x] ,最终max_point 所对应的max_sum就是所要求的k

## codeforces Educational Codeforces Round 151 (Rated for Div. 2) A. Forbidden Integer

来源同上，一个简单的完全背包问题。

## ACwing 1086. 恨7不成妻

采用递归写法可以比采用循环写法简单很多。
数位DP的题目都遵循同一套思考逻辑，使用递归写法都较循环写法更加简单。

## ACwing 135. 最大子序和

这个题有两个值得注意的细节
1 为什么初始时tt是0而不是-1？
     因为初始时要加入s[0],例如最优解是1到i的所有数字之和，这时就应该计算s[i]-s[0]，所以一开始就要把s[0]加入进来。
2 为什么在42行不用判断队列是否为空？
     因为一开始就加入了s[0]，所以队列总是不可能为空。

## ACwing 1088. 旅行问题

前后做两次对称的单调队列优化DP，要尤其注意边界问题。

## ACwing 1089 烽火传递

一开始错误的地方：一开始默认把a[1]加入了单调队列，导致答案错误。
正解：一开始应该先放一个零在单调队列里，因为在第一个点燃的烽火台前面是没有烽火台被点燃的。

## AcWing 1090. 绿色通道

这道题就是上一道烽火传递+二分。

## AcWing 1087. 修剪草坪  

这道题反过来考虑先取最小值，再用总和减去最小值，就是和烽火传递一模一样的题目。

## ACwing 300. 任务安排1

这道题的细节在于会爆炸int，如果不把数组都定义成long long的话，需要把转移方程写成这样：
f[i] = min(f[i], f[j] + (LL) s * (c[n]- c[j]) + (LL) t[i] * (c[i] - c[j]));
因为t[]和c[]两个数字相乘可能会爆int，变成负数，所以要先转换成long long

## ACwomg 301. 任务安排2

这道题就是上一道题的斜率优化版本。

## ACwing 302. 任务安排3

这道题是上一道题的二分版本。
注意凸包的维护是
```
while (hh < tt && (double)(f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt]]) >= (double) (c[q[tt]] - c[q[tt - 1]]) * (f[i] - f[q[tt]]))  tt--;
```
而不是
```
while (hh < tt && (double)(f[q[tt]] - f[q[tt - 1]]) * (c[i] - c[q[tt]]) > (double) (c[q[tt]] - c[q[tt - 1]]) * (f[i] - f[q[tt]]))tt--;
```
是大于等于而不是大于。

## ACwing 303.运输小猫

这道题的斜率优化采用的是二位状态f[i][j]，表示用i个饲养员，回收j只小猫的最优解。
前面的任务安排不需要把f数组初始化为正无穷，因为所有的f[i]都是从初始的f[0]转换而来，只要把f[0]设置为合法的初始值即可。
而这道题，正确的初始化应该是：
```
memset(f, 0x3f, sizeof f);
for (int i = 0; i <= p; i ++ ) f[i][0] = 0;

```
状态计算：
```
for (int i = 1; i <= m; i ++ )
        {
            while (hh < tt && (get_y(q[hh + 1], j) - get_y(q[hh], j)) <= a[i] * (q[hh + 1] - q[hh])) hh ++ ;
            int k = q[hh];
            f[j][i] = f[j - 1][k] - a[i] * k + s[k] + a[i] * i - s[i];
            while (hh < tt && (get_y(q[tt], j) - get_y(q[tt - 1], j)) * (i - q[tt]) >=
                (get_y(i, j) - get_y(q[tt], j)) * (q[tt] - q[tt - 1])) tt -- ;
            q[ ++ tt] = i;
        }

```
如果初始化时不加上memset的话，那么在计算f[1][i]时就会出错，因为计算f[1][i]时会调用f[0][k]，其中k不等于零，这个值是非法的，应该被设置为正无穷才对，但是因为我们没有初始化，所以f[1][i]直接由它转移而来，最终导致所有的f[][]计算结果均为零。

## AcWing 1097. 池塘计数

广搜flood fill模板提。

## AcWing 1098. 城堡问题

这种类型的题目要小心是m行n列还是n行m列。

## ACwing 1106. 山峰和山谷

这道题要注意广搜中的一个细节：
```
if(i == nx && j == ny) continue;
            if(i < 1 || i > n) continue;
            if(j < 1 || j > n) continue;
            if(w[i][j] != w[nx][ny])
            {
                if(w[i][j] > w[nx][ny]) is_peak = false;
                else is_valley = false;
                continue;
            }
            if(st[i][j]) continue;
```
在这一系列的判定条件中，不能把st的那个判定条件放在高度判定条件的前面，否则在计数最后一块没有被遍历的空地时，就会直接全部跳过高度判定，导致山峰数量和山谷数量同时加一。