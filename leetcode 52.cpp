// 按照行搜索
class Solution {
    public:
     std::vector<bool> col, diag1, diag2;
     int ans = 0;
     int totalNQueens(int n) {
         col.assign(n + 1, false);
         diag1.assign(2 * n, false);
         diag2.assign(2 * n, false);
         dfs(0, n);
         return ans;
     }
     void dfs(int rn, int n) {
         // 到了这一行肯定都放好了，直接ans++
         if (rn == n) {
             ans++;
             return;
         }
         // 枚举放在哪一列，因为n*n的棋盘要放n个，所以每行都必须放一个，没得选
         for (int i = 0; i < n; i++) {
             if (col[i] || diag1[rn + i] || diag2[rn - i + n]) continue;
             col[i] = true;
             diag1[rn + i] = true;
             diag2[rn - i + n] = true;
             dfs(rn + 1, n);
             col[i] = false;
             diag1[rn + i] = false;
             diag2[rn - i + n] = false;
         }
     }
 };

// 按照格子搜索
class Solution {
    public:
     std::vector<bool> col, diag1, diag2, row;
     int ans = 0;
     int totalNQueens(int n) {
         col.assign(n + 1, false);
         diag1.assign(2 * n, false);
         diag2.assign(2 * n, false);
         row.assign(n + 1, false);
         dfs(0, 0, n, 0);
         return ans;
     }
     void dfs(int x, int y, int n, int cnt) {
         if (cnt == n) {
             ans++;
             return;
         }
         if (y == n) dfs(x + 1, 0, n, cnt);
         if (x == n) {
             return;
         }
         // 不放
         dfs(x, y + 1, n, cnt);
         // 放
         if (!row[x] && !col[y] && !diag1[x + y] && !diag2[x - y + n]) {
             row[x] = col[y] = diag1[x + y] = diag2[x - y + n] = true;
             dfs(x, y + 1, n, cnt + 1);
             row[x] = col[y] = diag1[x + y] = diag2[x - y + n] = false;
         }
     }
 };