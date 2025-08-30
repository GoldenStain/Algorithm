class Solution {
public:
  int findNumberOfLIS(vector<int> &nums) {
    int n = nums.size(), m = discrete(nums);
    BIT bit(m);
    for (int x : nums) {
      auto [f, g] = bit.query(x - 1);
      bit.update(x, {f + 1, std::max(g, 1)});
    }
    return bit.query(m).g;
  }

private:
  struct T;
  struct BIT {
    int upper;
    std::vector<T> arr;
    BIT(int x) : upper(x) { arr.resize(upper + 1, {0, 0}); }
    void update(int pos, const T &x) {
      while (pos <= upper) {
        if (x.f > arr[pos].f)
          arr[pos].g = 0;
        if (x.f >= arr[pos].f)
          arr[pos].g += x.g;
        arr[pos].f = std::max(arr[pos].f, x.f);
        pos += pos & (-pos);
      }
    }
    T query(int pos) {
      T res;
      while (pos) {
        if (arr[pos].f > res.f)
          res.g = 0;
        if (arr[pos].f >= res.f)
          res.g += arr[pos].g;
        res.f = std::max(res.f, arr[pos].f);
        pos -= pos & (-pos);
      }
      return res;
    }
  };
  struct T {
    int f = 0, g = 0; // 最大值和个数
  };
  int discrete(std::vector<int> &arr) {
    std::vector<int> b{arr.begin(), arr.end()};
    std::sort(b.begin(), b.end());
    b.erase(std::unique(b.begin(), b.end()), b.end());
    int size = b.size();
    for (int &ai : arr) {
      ai = std::lower_bound(b.begin(), b.end(), ai) - b.begin() + 1;
    }
    return size;
  }
};