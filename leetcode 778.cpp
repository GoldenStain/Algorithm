// 最短路解法
using PII = std::pair<int, int>;
class Solution {
public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();
    vector dist(n, vector<int>(n, 0x3f3f3f3f));
    vector vis(n, vector<char>(n, false));
    std::priority_queue<PII, vector<PII>, std::greater<>> pq;
    pq.push({grid[0][0], 0});
    dist[0][0] = grid[0][0];
    while (!pq.empty()) {
      auto tmp = pq.top();
      pq.pop();
      int dis_now = tmp.first, x = tmp.second / n, y = tmp.second % n;
      if (vis[x][y])
        continue;
      vis[x][y] = true;
      for (int k = 0; k < 4; k++) {
        int i = x + dx[k], j = y + dy[k];
        if (i < 0 || i >= n || j < 0 || j >= n)
          continue;
        int idea_dis = std::max(grid[i][j], dist[x][y]);
        if (dist[i][j] > idea_dis) {
          dist[i][j] = idea_dis;
          pq.push({dist[i][j], i * n + j});
        }
      }
    }
    return dist[n - 1][n - 1];
  }

private:
  int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
};

// 二分解法
using PII = std::pair<int, int>;
class Solution {
public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<PII> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int l = 0, r = n * n;
    std::vector vis(n, std::vector<char>(n, false));
    auto check = [&](int thre) -> bool {
      vis.assign(n, vector<char>(n, false));
      if (thre < grid[0][0])
        return false;
      std::queue<PII> q;
      q.push({0, 0});
      while (!q.empty()) {
        PII tmp = q.front();
        int x = tmp.first, y = tmp.second;
        q.pop();
        if (vis[x][y])
          continue;
        vis[x][y] = true;
        for (auto &[dx, dy] : dirs) {
          int i = x + dx, j = y + dy;
          if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] > thre)
            continue;
          q.push({i, j});
        }
      }
      return vis[n - 1][n - 1];
    };
    while (l < r) {
      int mid = (l + r) >> 1;
      if (check(mid)) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return l;
  }
};
// 并查集
using PII = std::pair<int, int>;
class Solution {
public:
  int swimInWater(vector<vector<int>> &grid) {
    int n = grid.size();
    vector<PII> index(n * n);
    fa.resize(n * n);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        index[grid[i][j]] = {i, j};
        fa[i * n + j] = i * n + j;
      }
    vector<PII> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int thre = 0; thre < n * n; thre++) {
      auto [x, y] = index[thre];
      for (auto &[dx, dy] : directions) {
        int i = x + dx, j = y + dy;
        if (i < 0 || i >= n || j < 0 || j >= n || grid[i][j] > thre)
          continue;
        int pa = find(x * n + y), pb = find(i * n + j);
        merge(pa, pb);
      }
      if (find(0) == find(n * n - 1))
        return thre;
    }
    return n * n - 1;
  }

private:
  vector<int> fa;
  void merge(int a, int b) { fa[b] = a; }
  int find(int x) {
    if (x == fa[x])
      return x;
    return fa[x] = find(fa[x]);
  }
};