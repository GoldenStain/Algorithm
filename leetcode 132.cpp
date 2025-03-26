class Solution {
   public:
    int minCut(string s) {
        int n = s.size();
        if (n == 1) {
            return 0;
        }
        vector<vector<bool>> g(n, vector<bool>(n, false));
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                if (i + 1 > j - 1)
                    g[i][j] = (s[i] == s[j]);
                else
                    g[i][j] = g[i + 1][j - 1] & (s[i] == s[j]);
            }
        }
        vector<int> f(n, 3000); // 要求min，记得初始化成inf
        for (int i = 0; i < n; i++) {
            if (g[0][i]) {
                f[i] = 0;
                continue;
            }
            for (int j = 0; j < i; j++) {
                if (g[j + 1][i]) f[i] = std::min(f[i], f[j] + 1);
            }
        }
        return f[n - 1];
    }
};