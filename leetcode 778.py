from typing import List
import heapq as pq
class Solution:
    def swimInWater(self, grid: List[List[int]]) -> int:
        n = len(grid)
        dist = [([0x3f3f3f3f] * n) for _ in range(n)]
        vis = [([False] * n) for _ in range(n)]
        q = []
        dist[0][0] = grid[0][0]
        pq.heappush(q, (dist[0][0], 0, 0))
        while len(q):
            dis, x, y = pq.heappop(q)
            if vis[x][y]:
                continue
            vis[x][y] = True
            for (dx, dy) in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                i = x + dx
                j = y + dy
                if i < 0 or i >= n or j < 0 or j >= n:
                    continue
                new_dis = max(dis, grid[i][j])
                if new_dis < dist[i][j]:
                    dist[i][j] = new_dis
                    pq.heappush(q, (dist[i][j], i, j))
        return dist[n - 1][n - 1]