class Solution {
    public:
        int maxPoints(vector<vector<int>>& points) {
            using PII = pair<int, int>;
            int n = points.size();
            if (n <= 2) return n;
            int ans = 0;
            for(int i = 0; i < n; i++) {
                std::unordered_map<int, int> M;
                if (ans > n - i || ans > n / 2)    
                    break;
                for(int j = i + 1; j < n; j++) {
                    int y = points[j][1] - points[i][1], x = points[j][0] - points[i][0];
                    if (x < 0) {
                        y = -y;
                        x = -x;
                    }
                    if (x && y)
                    {
                        int g = gcd(x, y);
                        x /= g;
                        y /= g;
                    }
                    if (!x)
                        y = 1;
                    if (!y)
                        x = 1;
                    M[x * (2e4 + 1) + y]++;
                }
                int maxnn = 0;
                for(auto &pi: M) {
                    maxnn = max(maxnn, pi.second + 1);
                }
                ans = max(ans, maxnn);
            }
            return ans;
        }
    private:
        int gcd(int x, int y) {
            return !y?x:gcd(y, x % y);
        }
    };