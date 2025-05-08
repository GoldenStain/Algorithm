class Solution {
public:
  int minTimeToReach(vector<vector<int>> &moveTime) {
    constexpr int MOD = 0b11;
    std::priority_queue<_Point, std::vector<_Point>> q;
    int m = moveTime.size(), n = moveTime[0].size();
    std::vector<std::vector<int>> dist(m, vector<int>(n, 2e9));
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    q.push({0, 0, 0, 1});
    while (!q.empty()) {
      _Point temp = q.top();
      q.pop();
      if (temp.x == m - 1 && temp.y == n - 1) {
        return temp.dis;
      }
      if (vis[temp.x][temp.y])
        continue;
      vis[temp.x][temp.y] = 1;
      for (int i = 0; i < 4; i++) {
        int nx = temp.x + dx[i], ny = temp.y + dy[i];
        if (nx < 0 || nx >= m || ny < 0 || ny >= n)
          continue;
        int new_dis = std::max(temp.dis, moveTime[nx][ny]) + temp.cost;
        if (new_dis < dist[nx][ny]) {
          q.push({nx, ny, new_dis, temp.cost ^ MOD});
        }
      }
    }
    return dist[m - 1][n - 1];
  }

private:
  struct _Point {
    int x, y;
    int dis;
    int cost;
    // C++17可以在不写构造函数的情况下，直接用{}结构化初始化，但是C++14不行，需要显式地写一个
    _Point(int _x, int _y, int _dis, int _cost)
        : x(_x), y(_y), dis(_dis), cost(_cost) {}
    // 注意这个重载小于号必须是const，priority_queue对这个有硬性要求
    bool operator<(const _Point &other) const { return dis > other.dis; }
  };

  int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
};

// remove the attr cost
