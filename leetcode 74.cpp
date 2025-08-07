// wrong solution
// 这里位置转换的公式也是错的。
class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int l = 0, r = m * n - 1;
    int row, col, x;
    while (l < r) {
      int mid = (l + r) >> 1;
      row = mid / m, col = mid % n;
      x = matrix[row][col];
      if (x >= target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    // 这里的x是倒数第二轮循环，而不是最后一轮循环的，直接拿来用会出错
    return (x == target);
  }
};

// Right solution
class Solution {
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int l = 0, r = m * n - 1;
    std::function<int(int)> pos = [&](int pos) {
      int row = pos / n, col = pos % n;
      return matrix[row][col];
    };
    while (l < r) {
      int mid = (l + r) >> 1;
      if (pos(mid) >= target) {
        r = mid;
      } else {
        l = mid + 1;
      }
    }
    return pos(l) == target;
  }
};