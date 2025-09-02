from typing import List

class Solution:
    def maximalRectangle(self, matrix: List[List[str]]) -> int:
        def computeArea(heights):
            stk = [-1] # 因为单调栈是严格递增的，所以这里需要padding -1
            res = 0
            for i in range(0, len(heights)):
                while len(stk) > 1 and heights[stk[-1]] >= heights[i]:
                    h_now = heights[stk.pop()] # pop()方法是有返回值的
                    left = stk[-1]; right = i
                    res = max(res, h_now * (right - left - 1))
                stk.append(i)
            return res

        m = len(matrix); n = len(matrix[0])
        ans = 0
        heights = [0] * (n+1) # 因为我们用的是>=号，所以padding0或者-1，都是对的
        for i, row in enumerate(matrix):
            for j, x in enumerate(row):
                # heights[j] = 0 if (x == '0') else (heights[j] + 1)
                if x == '0':
                    heights[j] = 0
                else:
                    heights[j] += 1
            ans = max(ans, computeArea(heights))
        return ans