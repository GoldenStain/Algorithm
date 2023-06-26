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
