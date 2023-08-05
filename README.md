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
