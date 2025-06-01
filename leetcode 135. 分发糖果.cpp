// my solution
class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    if (n == 1)
      return 1;
    std::vector<int> candys(n, 0);
    using PII = pair<int, int>;
    priority_queue<PII, std::vector<PII>, std::greater<PII>> q;
    for (int i = 0; i < n; i++) {
      q.push({ratings[i], i});
    }
    int ans = 0;
    while (q.size()) {
      PII t = q.top();
      q.pop();
      int pos = t.second, t1, t2;
      // printf("pos: %d", pos);
      if (t.second == 0)
        t1 = t2 = 1;
      else if (t.second == n - 1)
        t1 = t2 = pos - 1;
      else {
        t1 = pos - 1;
        t2 = pos + 1;
      }
      t1 = ratings[pos] > ratings[t1] ? candys[t1] + 1 : 1;
      t2 = ratings[pos] > ratings[t2] ? candys[t2] + 1 : 1;
      candys[pos] = max(t1, t2);
      candys[pos] = candys[pos] == 0 ? 1 : candys[pos];
      // printf("t1 : %d, t2: %d, candys: %d\n", t1, t2, candys[pos]);
      ans += candys[pos];
    }
    return ans;
  }
};

// O(2n) solution
class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    vector from_left(n, 1), from_right(n, 1);
    int res = 0;
    for (int i = 1; i < n; i++) {
      from_left[i] = (ratings[i] <= ratings[i - 1]) ? (1) : (from_left[i - 1] + 1);
    }
    res += std::max(from_left[n - 1],  from_right[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
      from_right[i] = (ratings[i] <= ratings[i + 1]) ? (1) : (from_right[i + 1] + 1);
      res += std::max(from_left[i], from_right[i]);
    }
    return res;
  }
};