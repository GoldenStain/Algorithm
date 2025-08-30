from typing import List
from dataclasses import dataclass
import bisect

@dataclass
class T:
    f: int = 0
    g: int = 0

class BIT:
    def __init__(self, upper):
        self.upper = upper
        # T是可变对象，导致这里数组中所有元素本质上都是同一个T实例
        # self.arr = [T(0, 0)] * (upper + 1)
        self.arr = [T(0, 0) for _ in range(upper + 1)]
    def query(self, pos: int):
        f = 0; g = 0
        while pos:
            if f < self.arr[pos].f:
                g = 0
            if f <= self.arr[pos].f:
                g += self.arr[pos].g
            f = max(f, self.arr[pos].f)
            pos -= (pos & (-pos))
        return T(f, g)

    def update(self, pos:int, x: T):
        while pos <= self.upper:
            if x.f > self.arr[pos].f:
                self.arr[pos].g = 0
            if x.f >= self.arr[pos].f:
                self.arr[pos].g += x.g
            self.arr[pos].f = max(self.arr[pos].f, x.f)
            pos += (pos & (-pos))

def discrete(nums):
    vals = set(nums)
    vals = sorted(vals)
    for i in range(len(nums)):
        nums[i] = bisect.bisect_left(vals, nums[i]) + 1
    return len(vals)


class Solution:
    def findNumberOfLIS(self, nums: List[int]) -> int:
        n = len(nums)
        m = discrete(nums)

        bit = BIT(m)
        for x in nums:
            t = bit.query(x - 1)
            f = t.f; g = t.g
            bit.update(x, T(f + 1, max(g, 1)))
        return bit.query(m).g