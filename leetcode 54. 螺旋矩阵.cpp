// solution 1
class Solution {
    public:
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
            std::vector<int> ans;
            int cnt = 0;
            int x = 0, y = 0, m = matrix.size(), n = matrix[0].size();
            int dx[4] = {0,1, 0, -1}, dy[4] = {1,0,-1,0}, dir = 0;
            std::vector<std::vector<bool>> flag(m, std::vector<bool>(n, false));
            while(cnt < m * n) {
                flag[x][y] = true;
                ans.push_back(matrix[x][y]);
                int nx = x + dx[dir], ny = y + dy[dir];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || flag[nx][ny])
                    dir = (dir + 1) % 4;
                x = x + dx[dir], y = y + dy[dir];
                cnt++;
            }
            return ans;
        }
    };

// solution 2
class Solution {
    public:
        vector<int> spiralOrder(vector<vector<int>>& matrix) {
            std::vector<int> ans;
            int m = matrix.size(), n = matrix[0].size();
            int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
            int dir = 0;
            int x = 0, y = 0;
            int top = 0, bottom = m - 1, left = 0, right = n - 1;
            while(top <= bottom && left <= right) {ans.push_back(matrix[x][y]);
                int nx = x + dx[dir], ny = y + dy[dir];
                if (nx < top || nx > bottom || ny < left || ny > right) {
                    if (dir == 0) top++;
                    else if (dir == 1) right--;
                    else if (dir == 2) bottom--;
                    else if (dir == 3) left++;;
                    dir = (dir + 1) % 4;
                }
                x = x + dx[dir]; y = y + dy[dir];
            }
            return ans;
        }
    };