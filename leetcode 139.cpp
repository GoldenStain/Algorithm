// greedy solution(wrong)
class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        std::unordered_set<std::string> S;
        for (auto& si : wordDict) {
            S.insert(si);
        }
        int hh = 0, tt = -1, len = s.size();
        while (tt < len) {
            tt++;
            std::string tmp = s.substr(hh, tt - hh + 1);
            if (S.find(tmp) != S.end()) {
                hh = tt + 1;
            }
        }
        return (hh == len);
    }
};

// DP solution
class Solution {
    using string = std::string;

   public:
    bool wordBreak(string s, std::vector<string> dicts) {
        std::unordered_set<int> S;
        std::unordered_set<string> dict_s;
        for (auto& si : dicts) {
            dict_s.insert(si);
        }
        int len = s.size();
        // 开始的时候可以插入一个-1，这样在循环内部就不用写特判了。
        S.insert(-1);
        for (int i = 0; i < len; i++) {
            for (const int& pos : S) {
                string tmp = s.substr(pos + 1, i - pos);
                if (dict_s.find(tmp) != dict_s.end()) {
                    S.insert(i);
                }
            }
        }
        return S.find(len - 1) != S.end();
    }
};

// faster DP
class Solution {
    using string = std::string;

   public:
    bool wordBreak(string s, std::vector<string> dicts) {
        int len = s.size();
        std::vector<int> dp(len+1, false);
        // 这里有一个小技巧：
        // 我们要保证能正常更新，我们必须要有一个为true的边界条件作为起点
        // 但是如果我们令dp[0]=true,在s长度只有1的时候，如s="a", dicts={"b"}
        // 这时候会误判
        // 我们把dp的下标范围平移到[1, len]
        // 每次更新的时候也就把下标+1，最后返回的答案就是dp[len]
        // 这样在长度仅为1的时候就不会误判了。
        dp[0] = true;
        for (int i = 0; i < len; i++) {
            // 没必要进行转移
            if (!dp[i])
                continue;
            for (int j = 0; j < dicts.size(); j++) {
                int jlen = dicts[j].size();
                // 如果后面的元素个数不足jlen个，substr函数会自己截断。
                string tmp =s.substr(i, jlen);
                if (tmp == dicts[j]) {
                    dp[i + jlen] = true;
                }
            }
        }
        return dp[len];
    }
};