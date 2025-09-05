from typing import List
from heapq import heappush, heappop, heapify

class Solution:
    def trapRainWater(self, heightMap: List[List[int]]) -> int:
        m = len(heightMap); n = len(heightMap[0])
        hq = []
        # 首尾两行
        for j in range (0, n):
            hq.append((heightMap[0][j], 0, j))
            hq.append((heightMap[m - 1][j], m - 1, j))
            heightMap[0][j] = -1
            heightMap[m - 1][j] = -1
        # 首尾两列
        for i in range(1, m - 1):
            hq.append((heightMap[i][0], i, 0))
            hq.append((heightMap[i][n - 1], i, n - 1))
            heightMap[i][0] = heightMap[i][n - 1] = -1
        heapify(hq)

        ans = 0
        while len(hq):
            minHeight, i, j = heappop(hq)
            for x, y in ((i - 1, j), (i + 1, j), (i, j + 1), (i, j - 1)):
                if x < 0 or x >= m or y < 0 or y >= n or heightMap[x][y] < 0:
                    continue
                ans += max(0, minHeight - heightMap[x][y])
                heappush(hq, (max(minHeight, heightMap[x][y]), x, y))
                heightMap[x][y] = -1
        
        return ans

        