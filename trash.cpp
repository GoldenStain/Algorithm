#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
#include <ios>
#include <iostream>
#include <istream>
#include <queue>

using PII = std::pair<int, int>;

constexpr int N = 1e5;
int n;
PII intervals[N];
int st, ed;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cin >> st >> ed;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::cin >> intervals[i].first >> intervals[i].second;
  }
  std::sort(intervals, intervals + n, [](const PII &a, const PII &b) -> bool {
    return a.first < b.first;
  });
  int ans = 0;
  bool successful = false;
  for (int i = 0; i < n; i++) {
    int j = i, cur_right = INT_MIN;
    while (j < n && intervals[j].first <= st) {
      cur_right = std::max(cur_right, intervals[j].second);
      j++;
    }
    i = j - 1;
    if (cur_right < st) {
      break;
    }
    ans++;
    if (cur_right >= ed) {
      successful = true;
      break;
    }
    st = cur_right;
  }
  if (!successful)
    std::cout << "-1\n";
  else 
    std::cout << ans << std::endl;
  return 0;
}
