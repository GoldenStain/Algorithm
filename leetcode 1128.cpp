class Solution {
public:
  int numEquivDominoPairs(vector<vector<int>> &dominoes) {
    unordered_map<int, int> M;
    for (int i = 0; i < dominoes.size(); i++) {
      int a = std::min(dominoes[i][0], dominoes[i][1]);
      int b = std::max(dominoes[i][0], dominoes[i][1]);
      M[a * 10 + b]++;
    }
    long long ans = 0ll;
    for (std::pair<const int, int> &pi : M) {
      long long t = static_cast<long long>(pi.second);
      ans += t * (t - 1) / 2;
    }
    return ans;
  }
};