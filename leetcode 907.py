from typing import List
class Solution:
    M = 1e9 + 7
    def sumSubarrayMins(self, arr: List[int]) -> int:
        arr.append(-1)
        n = len(arr)
        stk = [-1]
        ans = 0
        for i in range(0, n):
            while len(stk) > 1 and arr[stk[-1]] >= arr[i]:
                center = stk.pop()
                left = stk[-1]; right = i
                ans = (ans + arr[center] * (right - center) * (center - left)) % self.M
            stk.append(i)
        return int(ans)