// BFS version
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    std::vector edges(numCourses, std::vector<int>{});
    std::vector in_d(numCourses, 0);
    // 连边
    for (auto &pi : prerequisites) {
      int a = pi[0], b = pi[1];
      edges[b].push_back(a);
      in_d[a]++;
    }
    // 拓扑排序
    std::queue<int> q;
    std::vector<int> ans;
    for (int i = 0; i < numCourses; i++)
      if (!in_d[i])
        q.push(i);
    while (q.size()) {
      int q_head = q.front();
      q.pop();
      ans.push_back(q_head);
      for (int to_i : edges[q_head]) {
        in_d[to_i]--;
        if (!in_d[to_i])
          q.push(to_i);
      }
    }
    if (ans.size() < numCourses)
      return std::vector<int>{};
    return ans;
  }
};

// DFS version
class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    std::vector edges(numCourses, std::vector<int>{});
    // 连边
    for (auto &pi : prerequisites) {
      int a = pi[0], b = pi[1];
      edges[b].push_back(a);
    }
    // 拓扑排序
    std::vector<int> ans;
    std::vector<char> vis(numCourses, 0); // 0未遍历，1遍历中，2遍历过
    std::function<bool(int)> dfs;
    dfs = [&](int cur) -> bool {
      if (vis[cur] == 1)
        return false;
      vis[cur] = 1;
      for (int to_i: edges[cur]) {
        if (vis[to_i] == 2)
          continue;
        if (!dfs(to_i))
          return false;
      }
      vis[cur] = 2;
      ans.push_back(cur);
      return true;
    };
    for (int i = 0; i < numCourses; i++) {
      if (vis[i])
        continue;
      if (!dfs(i)) {
        return std::vector<int> {};
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};