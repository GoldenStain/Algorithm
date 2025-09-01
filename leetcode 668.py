class Solution:
    def findKthNumber(self, m: int, n: int, k: int) -> int:
        def check(x):
            bound = x // n
            cnt = bound * n
            for i in range(bound + 1, m + 1):
                cnt += x // i
            return cnt >= k
        l = 0; r = m*n
        while l < r:
            mid = (l + r) >> 1
            if check(mid):
                r = mid
            else:
                l = mid + 1
        return l
