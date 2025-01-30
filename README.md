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

## leetcode 11. Container With Most Water

首先不用想，这道题的正解显然是双指针。
一开始我的想法是把l,r的初始位置都放在0,然后一起向右移动,但是这个思路完全不可行，因为在指针移动过程中，h[l]和h[r]的变化是不确定的,区间的长度变化也是不确定的，可能l追r变小,也可能r远离l变大,根本无从下手.
于是我想到,把l和r分别放在0和n - 1这两个一头一尾的起始位置,这样的话每次移动指针就必然导致区间长度的缩短,就可以专心解决h[l]和h[r]的变化问题.
一开始写的是:
```
class Solution {
public:
    int maxArea(vector<int>& height) {
        int n = height.size();
        vector <int>& h = height;
        int l = 0, r = n - 1, now = min(h[l], h[r]);
        int ans = now * (r - l);
        while(l < r)
        {
            int a = min(h[l + 1], h[r]), b = min(h[l], h[r - 1]);
            if(a > b) l++, now = a;
            else r--, now = b;
            ans = max(ans, now * (r - l));
        }
        return ans;
    }
};
```
根据移动之后min(h[l],h[r])的大小来决定移动的方式,但是这样只能过一半的点,这个做法的错误之处在于:
每次移动后,确实能够保证移动后的两个可能结果中,我们得到了较大的那一个,但是可能这两者都没有原来的大,我们只比较了移动后的两种结果大小,却忘记了和原来的计算结果进行比较,导致移动指针后ans可能往变小的方向移动.
正解:
```
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1, ans = 0;
        while(l < r)
        {
            ans = max(ans, min(height[l], height[r]) * (r - l));
            if(height[l] > height[r]) r--;
            else l++;
        }
        return ans;
    }
};
```
每次h[l]和h[r]当中较小的那个就是限制因素,每次移动着力于试图让限制因素变大,从而让系统往潜在的变大方向移动.

## ACwing 1076.迷宫问题

这道题有两个值得注意的点：
### 1.
如果从(0,0)开始走到终点的话，那么最终的序列需要反着输出；但是如果从终点反向搜索到起点，那么最后只需要正着输出就可以了.
### 2.
最后输出时的细节处理:
```
while(true)
    {
        cout << end.x << ' ' << end.y << endl;
        if(end.x == n - 1 && end.y == n - 1) break;
        end = Pre[end.x][end.y];
    }
```
如果要用while或者do while来判断循环是否结束,因为```end.x == n - 1 && end.y == n - 1```这个条件是在循环内部达成的,所以无论是while还是do while,都无法做到恰到好处地停止.所以需要采取这种循环内部更新,同时循环内部判断的方式来控制这个循环.

## ACwing 188.武士风度的牛

这个题没有什么值得注意的点.

## ACwing 1100.抓住那头牛

这道题可以通过一点简单的数学推导,分析出最大需要开多少的数组以节省空间.

## ACwing 173. 矩阵距离

多源最短路问题可以通过添加一个虚拟源点从而转换成为普通的单源最短路问题.

## ACwing 1107.魔板

这道题和八数码类似，甚至可以说更加简单。注意如何进行魔板的变换以及方案的存储和输出。
另外，这道题可以引出一个非常有意思的问题：
如何优雅地实现顺时针遍历？
我们可以借助广搜的思想，避免一些数学上寻找下标对应关系的操作。
首先，像广搜一样创建dx和dy数组，表示移动的方向；创建st数组，存储每个位置是否遍历过，然后从起始位置开始，先一直往一个方向走，在碰到边界或已经遍历过的点时，就让当前表示方向的下标i加上1再取模4，这样就可以实现循环切换方向，直至遍历完所有需要遍历的点。

## ACwing 175. 电路维修

这道题的重点在于
1.点和格子下标的对应关系
2.因为点比格子多了一行一列，所以点的取值范围是从(0,0)到(n,m).

## ACwing 190. 字串变换

这道题
```
if (db.count(ns))
    return d0 + db[ns] + 1;
```
一搜到就return这里，看似和每次都扩展一层矛盾，实际上是完全正确的。
因为这个搜索能进行到这一步，所以之前的操作都没有得到答案，说明之前每一层都是完整扩展了的，那么即便我们当前搜索的这个节点s0所在的层，存在一个s1也能搜到答案，这个新答案也一定大于等于当前答案的，所以直接return是正确的。

## leetcode54. Spiral Matrix
模拟绕圈即可。

## leetcode31. next permutation

这道题可以先从极端情况入手考虑：
1. 第一个全排列：
	
	`1 2 3 4 5`，完全升序的
2. 最后一个全排列：
	
	`5 4 3 2 1`，完全降序的

有一个很显然的结论：为了最小化我们的操作对字典序的影响，我们要尽量修改靠后的元素的顺序。
所以，我们能确定，我们需要从后向前扫描，寻找需要交换的元素。

而我们也已经确定，如果一段序列是单调下降的，那么它的字典序就没有增大的余地，所以我们可以得到这样的做法：

从后向前扫描，跳过单调递增的部分（对应正序的单调下降），在第一个转折点处，记录当前的元素，然后找到后面最小的、比这个点大的元素，对他们进行交换，然后对整个序列靠后的部分进行逆序，可以通过图片很直观地理解：

[![pAqxldg.png](https://s21.ax1x.com/2024/12/16/pAqxldg.png)](https://imgse.com/i/pAqxldg)

由于交换后，最后的一堆元素是倒序的，字典序是新顺序当中最大的，我们reverse一遍，就能变成最小的了。

代码：https://www.cnblogs.com/smartljy/p/18611098

## ACwing1524. 最长回文子串

因为这个题的数据范围只有1000，所以能O(n)枚举，枚举回文子串的中点，然后向两边延展，看看极限长度是多少，注意每次要区分奇数长度字串和偶数长度字串，两种的计算方式不一样。

## P8638 [蓝桥杯 2016 省 A] 密码脱落

DP求获得回文串的最小步数：
`f[l][r] = (s[l] == s[r]) ? f[l + 1][r - 1] : std::min(f[l + 1][r], f[l][r - 1]) + 1;`

## leetcode155. 最小栈
用两个栈，一个用来存本身，一个用来存最小值。

## 循环方式遍历二叉树

可以参考这个链接：[循环遍历二叉树](https://www.cnblogs.com/smartljy/p/18694838)。

## Leetcode 150. Evaluate Reverse Polish Notation

每遇到一个操作符，就把栈顶部的两个数字拿出来进行运算，最后的结果就是栈顶的数字。

## Leetcode 224.Basic Calculator II

具体题解：[栈模拟中缀表达式求值](https://www.acwing.com/solution/content/69284/)
这道题要注意的点：
1. 负号的判定

    如果在一开始出现减号，或者减号前面是一个左括号，那么当前这个减号就是一个负号。
2. 在遇到数字取出数字的时候，有一个细节

    一开始的写法是：`res = res * 10 + s[j] - '0';` 这样会先给res * 10 加上s[j]最后再去减去'0'，如果遇到的数字是2147483647，明明是能够用int存下的，但是我们在算2147483640+55的时候，就直接溢出了，所以我们需要给后面的s[j] - '0'整体加上一个括号，这样就不会溢出了。