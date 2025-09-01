using PII = std::pair<int, int>;

class Solution {
public:
  int carFleet(int target, vector<int> &position, vector<int> &speed) {
    int n = position.size();
    std::vector<PII> ps;
    for (int i = 0; i < n; i++) {
      ps.push_back({position[i], speed[i]});
    }
    std::sort(ps.begin(), ps.end());
    std::vector<double> stk;
    for (int i = n - 1; ~i; i--) {
      PII tmp = ps[i];
      double time_cost = 1.0 * (target - tmp.first) / tmp.second;
      // 只有每个车队的代表元素才会入队
      // 追不上前面车队，那么说明这辆车在一个新的车队当中
      // 利用性质1. 一个车队到达终点的时间，等于代表元素到达终点所耗费的时间
      if (stk.empty() || time_cost > stk.back())
        stk.push_back(time_cost);
    }
    return stk.size();
  }
};