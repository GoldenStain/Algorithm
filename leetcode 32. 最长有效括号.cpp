// DP
class Solution {
    public:
        int longestValidParentheses(string s) {
            int n = s.size();
            std::vector<int> f(n, 0);
            int ans = 0;
            for(int i = 1; i < n; i++) {
                if (s[i] == '(')
                    continue;
                if (s[i - 1] == '(')
                    // 这里要注意三目运算符的优先级问题
                    f[i] = ((i - 2) >= 0? f[i - 2] : 0) + 2;
                else if (i - 1 - f[i - 1] >= 0 && s[i - 1 - f[i - 1]] == '(')
                    f[i] = f[i - 1] + 2 + (i - 2 - f[i - 1] >=0 ?f[i - 2 - f[i - 1]]:0);
                ans = std::max(ans, f[i]);
            }
            return ans;
        }
    };

// 双指针写法
class Solution {
    public:
        int longestValidParentheses(string s) {
            int left = 0, right = 0;
            int n = s.size();
            int ans = 0;
            for(int i = 0; i < n; i++) {
                if (s[i] == '(')
                    left++;
                else
                    right++;
                if (left == right)
                    ans = std::max(ans, left*2);
                else if (right > left)
                    left = 0, right = 0;
            }
            left = 0; right = 0;
            for(int i =n - 1;i>=0; i--) {
                if (s[i] == '(')
                    left++;
                else
                    right++;
                if (left == right)
                    ans = std::max(ans, left*2);
                else if (left > right)
                    left = 0, right = 0;
            }
            return ans;
        }
    
    };