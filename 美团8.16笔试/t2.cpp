namespace leetcode {
template <typename T> using vector = std::vector<T>;
template <typename T> using function = std::function<T>;

constexpr int N = 1e3 + 5, M = (2e3 + 2) * 2;
constexpr int INF = 1e9;

// 链式前向星
std::array<int, N> h{};
std::array<int, M> ne{}, e{}, wei{};
int cnt = 0;

int n, m, k;

// int stones[N], stones_one_layer[N];
std::array<int, N> stones{}, stones_one_layer{};
std::array<bool, N> vis;

std::array<std::array<int, N>, 2> dist;

using PII = std::pair<int, int>;

class Solution {
public:
  void solve() {
    std::freopen("input.txt", "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    // 初始化
    for (auto &dk : dist) {
      std::fill(dk.begin(), dk.end(), INF);
    }
    dist[0][1] = 0;

    std::cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
      std::cin >> stones[i];
      stones_one_layer[i] = std::max(0, stones[i]);
    }
    int u, v, w;
    for (int i = 1; i <= m; i++) {
      std::cin >> u >> v >> w;
      add(u, v, w);
      add(v, u, w);
    }
    function<void(std::array<int, N> &)> DJ =
        [&](std::array<int, N> &Dist) -> void {
      std::fill(vis.begin(), vis.end(), false);
      // 初始化队列
      std::priority_queue<PII, vector<PII>, std::greater<PII>> q;
      for (int i = 1; i <= n; i++) {
        if (Dist[i] != INF) {
          q.push({Dist[i], i});
        }
      }
      while (q.size()) {
        auto p = q.top();
        q.pop();
        int id = p.second, dis = p.first;
        if (vis[id]) {
          continue;
        }
        vis[id] = true;
        for (int i = h[id]; i; i = ne[i]) {
          int _to = e[i];
          int new_dis = dis + stones_one_layer[_to] + wei[i];
          if (Dist[_to] > new_dis) {
            Dist[_to] = new_dis;
            q.push({Dist[_to], _to});
          }
        }
      }
    };
    int now = 0, nxt;
    int ans = INF;
    // 原图跑一遍DJ
    DJ(dist[0]);
    ans = std::min(dist[0][n], ans);
    while (k--) {
      nxt = now ^ 1;
      std::fill(dist[nxt].begin(), dist[nxt].end(), INF);
      // 在层之间连边
      for (int i = 1; i <= n; i++) {
        if (dist[now][i] >= INF) {
          continue;
        }
        for (int j = h[i]; j; j = ne[j]) {
          int _to = e[j];
          if (stones[_to] >= 0)
            continue;
          int new_dis = dist[now][i] + stones[_to] + wei[j];
          if (new_dis < dist[nxt][_to]) {
            dist[nxt][_to] = new_dis;
          }
        }
      }
      // 分层图跑DJ
      DJ(dist[nxt]);
      ans = std::min(ans, dist[nxt][n]);
      // 切换层
      now = nxt;
    }
    if (ans >= INF / 2) {
      std::cout << "NO\n";
    } else {
      std::cout << ans << "\n";
    }
  }

private:
  inline void add(int u, int v, int w) {
    ne[++cnt] = h[u];
    e[cnt] = v;
    h[u] = cnt;
    wei[cnt] = w;
  }
};
} // namespace leetcode