from typing import List

class Solution:
    def largestIsland(self, grid: List[List[int]]) -> int:

        area: List[int] = []
        n = len(grid)

        def dfs(i: int, j: int) -> int:
            size: int = 1
            grid[i][j] = len(area) + 2
            for x, y in ((i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)):
                if x < 0 or x >= n or y < 0 or y >= n or grid[x][y] != 1:
                    continue
                size += dfs(x, y)
            return size

        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                if x == 1:
                    area.append(dfs(i, j))

        # 没有岛屿
        if not area:
            return 1

        ans = 0

        # 人工填充
        for i , row in enumerate(grid):
            for j, x in enumerate(row):
                if x:
                    continue
                S = set()
                for nx, ny in ((i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)):
                    if nx < 0 or nx >= n or ny < 0 or ny >= n or not grid[nx][ny]:
                        continue
                    S.add(grid[nx][ny])
                ans = max(ans, 1 + sum(area[t - 2] for t in S))

        return n**2 if not ans else ans