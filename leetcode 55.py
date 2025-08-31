from typing import List

class Solution:
    def canJump(self, nums: List[int]) -> bool:
        # dp[i] 表示nums[0:i](不含i)从nums[0]开始所能跳跃的最远下标 这里不含i是有意义的
        # dp的初始化要注意 因为题目要求从nums[0]开始跳，说明一开始刚好可以达到nums[0], 因此dp[0]初始为0(表明不含nums[0]之前就已经能跳到下标0) 因此需要dp[0]以保证遍历时的操作统一
        # i从1开始更新, dp[i]的逻辑就是 如果dp[i-1](nums[0:i-1]不含nums[i-1])跳不到下标i-1的位置 则不用更新了(因为更跳不到末尾位置) 直接返回False
        # 若能跳到, 则dp[i] = max(dp[i-1], i-1 + nums[i-1])
        # 若dp被更新完 说明都能跳到 返回True
        n = len(nums)
        # dp = [0] * (n+1)
        # for i in range(1, n+1):
        #     if i-1 > dp[i-1]:
        #         return False
        #     else:
        #         # 跳跃得到当前 则包括当前的最远跳跃下标 为取二者的最大值
        #         dp[i] = max(dp[i-1], i-1+nums[i-1])
        # 因为上面只用到i-1 因此可以将i退化从0开始
        # for i in range(n):
        #     if i > dp[i]:
        #         return False
        #     else:
        #         dp[i+1] = max(dp[i], i + nums[i])
        # 从上可知可以用滚动数组因此更改如下
        dp = 0    # 前面解释过了 dp初始为0的含义
        for i in range(n):
            if i > dp:
                return False
            else:
                dp = max(dp, i + nums[i])
        return True