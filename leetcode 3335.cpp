constexpr int MOD = 1e9 + 7;

class Solution {
public:
  int lengthAfterTransformations(string s, int t) {
    int n = s.size();
    std::vector f(2, std::vector<int>(26, 0));
    int idx = 0;
    for (char c : s) {
      f[idx][c - 'a']++;
    }
    for (int i = 1; i <= t; i++) {
      idx = i & 1;
      f[idx][0] = f[idx ^ 1][25];
      f[idx][1] = (f[idx ^ 1][0] + f[idx ^ 1][25]) % MOD;
      for (int i = 2; i < 26; i++)
        f[idx][i] = f[idx ^ 1][i - 1];
    }
    int ans = 0;
    for (int i = 0; i < 26; i++)
      ans = (ans + f[idx][i]) % MOD;
    return ans;
  }
};

// matrix multiply solution
constexpr int MOD = 1e9 + 7;

class Solution {
public:
  int lengthAfterTransformations(string s, int t) {
    int n = s.size();
    std::vector f(1, vector<int>(26, 0));
    std::vector tmp_f = f;
    for (char c : s) {
      f[0][c - 'a']++;
    }
    std::vector matrix(26, std::vector<int>(26, 0));
    vector tmp_matrix = matrix;

    // 初始化权重矩阵
    matrix[25][0] = 1;
    matrix[0][1] = matrix[25][1] = 1;
    for (int j = 2; j < 26; j++)
      matrix[j - 1][j] = 1;

    // 快速幂
    while (t) {
      if (t & 1) {
        f = matMul(f, matrix, tmp_f);
      }
      matrix = matMul(matrix, matrix, tmp_matrix);
      t >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < 26; i++)
      ans = (ans + f[0][i]) % MOD;
    return ans;
  }

private:
  vector<vector<int>> matMul(vector<vector<int>> &A, vector<vector<int>> &B,
                             vector<vector<int>> &C) {
    int m = A.size(), k = A[0].size(), n = B[0].size();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int res = 0;
        for (int cnt = 0; cnt < k; cnt++) {
          res = (res + (long long)A[i][cnt] * B[cnt][j] % MOD) % MOD;
        }
        C[i][j] = res;
      }
    }
    return C;
  }
};