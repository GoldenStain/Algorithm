// BFS version
class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    std::queue<int> q;
    std::vector edges(numCourses, std::vector<int>{});
    std::vector in_cnt(numCourses, 0);
    for (auto &pi : prerequisites) {
      int a = pi[0], b = pi[1];
      edges[b].push_back(a);
      in_cnt[a]++;
    }
    for (int i = 0; i < numCourses; i++)
      if (in_cnt[i] == 0)
        q.push(i);
    int cnt_qed = 0;
    while (q.size()) {
      cnt_qed++;
      int head = q.front();
      q.pop();
      for (int dest : edges[head]) {
        in_cnt[dest]--;
        if (!in_cnt[dest])
          q.push(dest);
      }
    }
    return (cnt_qed == numCourses);
  }
};