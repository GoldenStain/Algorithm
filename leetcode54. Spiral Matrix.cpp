#include <iostream>
#include <vector>
#include <bitset>
#include <array>

class Solution {
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
        // m行，n列
        m = matrix.size(), n = matrix[0].size();
        int total_size = m*n;
        std::cout << total_size << std::endl;
        std::vector<int> ans(total_size, 0);
        std::vector<std::vector<bool>> flag(m, std::vector<bool>(n, false));
        int cnt = 0;
        int x = 0, y = 0;
        int d_idx = 0;
        int nx, ny;
        while(cnt < m * n) {
            flag[x][y] = true;
            ans[cnt++] = matrix[x][y];
            nx = x + dx[d_idx];
            ny = y + dy[d_idx];
            if(out_of_bound(nx, ny) || flag[nx][ny]) {
                d_idx = (d_idx + 1) % 4;
                nx = x + dx[d_idx];
                ny = y + dy[d_idx];
            }
            x = nx;
            y = ny;
        }
        return ans;
    }
private:
    int m, n;
    //  方向数组
    int dx[4] = {0, 1, 0, -1},
        dy[4] = {1, 0, -1, 0};
    bool out_of_bound(int x, int y) {
        if(x < 0 || x >= m)
            return true;
        if(y < 0 || y >= n)
            return true;
        return false;
    }
};
