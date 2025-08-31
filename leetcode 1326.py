from typing import List

class Solution:
    def minTaps(self, n: int, ranges: List[int]) -> int:
        right_bound = [0] * (n + 1) # 每个位置能延伸的右边界
        for i, rangei in enumerate(ranges):
            li = max(0, i - rangei)
            right_bound[li] = max(right_bound[li], i + rangei)
        cur_right = 0 # 当前已经存在的桥
        next_right = 0 # 下一座要修的桥
        ans = 0
        # 不需要遍历到最后一个位置
        for i in range(n):
            next_right = max(next_right, right_bound[i])
            # 到了当前桥的最远距离
            if i == cur_right:
                if next_right < i + 1:
                    # 到不了下一个位置了
                    return -1
                cur_right = next_right
                ans += 1
        return ans