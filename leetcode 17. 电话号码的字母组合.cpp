class Solution {
    public:
        vector<string> letterCombinations(string digits) {
            std::vector<string> ans;
            // 输入有可能有空
            if (digits.empty())
                return ans;
            int len = digits.size();
            search(ans, digits, 0, len, "");
            return ans;
        }
    private:
        std::string dict[15] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        void search(std::vector<string> &ans, string& digits, int now, int len, std::string s) {
            if (now == len) {
                ans.emplace_back(s);
                return;
            }
            int d = digits[now] - '0';
            cout << d <<std::endl;
            for(auto ci: dict[d]) {
                search(ans, digits, now + 1, len, s + ci);
            }
        }
    };