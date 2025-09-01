from typing import List

class Solution:
    def getCollisionTimes(self, cars: List[List[int]]) -> List[float]:
        n = len(cars)
        stk = []
        ans = [-1.0] * n
        for i in range(n - 1, -1, -1):
            pi = cars[i][0]; vi = cars[i][1]
            while stk:
                if stk and cars[stk[-1]][1] >= vi:
                    stk.pop()
                    continue
                # 没车了，说明i号车追不上前面的了
                if not stk:
                    break
                # 有车，但是需要变成追击对象
                T = (cars[stk[-1]][0] - pi) / (vi - cars[stk[-1]][1])
                if ans[stk[-1]] > 0 and T > ans[stk[-1]]:
                    stk.pop()
                    continue
                ans[i] = T
                break
            stk.append(i)
        return ans
