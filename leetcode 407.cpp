using PII = std::tuple<int, int, int>;
int moves[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

class Solution {
public:
  int trapRainWater(vector<vector<int>> &heightMap) {
    int m = heightMap.size(), n = heightMap[0].size();
    int ans = 0;
    std::priority_queue<PII, vector<PII>, std::greater<PII>> q;
    // 把容器四周的点先入队
    // 第一行，最后一行
    for (int j = 0; j < n; j++) {
      q.emplace(heightMap[0][j], 0, j);
      q.emplace(heightMap[m - 1][j], m - 1, j);
      heightMap[0][j] = -1; heightMap[m - 1][j] = -1; // 标记
    }
    // 第一列，最后一列
    // 调整循环边界，避免重复
    for (int i = 1; i < m - 1; i++) {
      q.emplace(heightMap[i][n - 1], i, n - 1);
      q.emplace(heightMap[i][0], i, 0);
      heightMap[i][n - 1] = heightMap[i][0] = -1;
    }
    // 开始求解
    while (q.size()) {
      auto [minHeight, i, j] = q.top();
      q.pop();
      for (auto &[dx, dy]: moves) {
        int nx = i + dx, ny = j + dy;
        if (nx < 0 || nx >= m || ny < 0 || ny >= n || heightMap[nx][ny] < 0)
          continue;
        ans += std::max(0, minHeight - heightMap[nx][ny]);
        q.emplace(std::max(minHeight, heightMap[nx][ny]), nx, ny);
        heightMap[nx][ny] = -1;
      }
    }
    return ans;
  }
};