class Solution {
public:
  int sumSubarrayMins(vector<int> &arr) {
    arr.push_back(-1); // padding
    int n = arr.size(), ans = 0;
    vector<int> stk;
    stk.push_back(-1); // padding
    for (int i = 0; i < n; i++) {
      while (stk.size() > 1 && arr[stk.back()] >= arr[i]) {
        int center = stk.back();
        stk.pop_back();
        int left = stk.back(), right = i;
        ans = (static_cast<long long>(ans) +
               arr[center] * (center - left) % M *
                   static_cast<long long>(right - center)) %
              M;
        // 因为M是1e9级别，所以不加static_cast的话，乘法会溢出int
      }
      stk.push_back(i);
    }
    return ans;
  }
};