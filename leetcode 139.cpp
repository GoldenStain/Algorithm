// greedy solution(wrong)
class Solution {
    public:
        bool wordBreak(string s, vector<string>& wordDict) {
            std::unordered_set<std::string> S;
            for (auto& si: wordDict) {
                S.insert(si);
            }
            int hh = 0, tt = -1, len = s.size();
            while(tt < len) {
                tt++;
                std::string tmp = s.substr(hh, tt - hh + 1);
                if (S.find(tmp) != S.end()) {
                    hh = tt + 1;
                }
            }
            return (hh == len);
        }
    };