#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

class Solution {
    using Umap = std::unordered_map<std::string, int>;
    using string = std::string;

   public:
    std::vector<int> findSubstring(string s, std::vector<string> &words) {
        std::unordered_map<std::string, int> _origin, _current;
        std::vector<int> ans;
        std::queue<int> q;
        for (auto &si : words) {
            _origin[si]++;
            _current[si] = 0;
        }
        // 起点
        int tot_len = words.size() * words[0].size(),
            sub_len = tot_len - words[0].size();

        for (int i = 0; i + words[0].size() <= s.size();) {
            std::cout << "i at beginning: " << i << std::endl;
            // 出队
            while (q.size() && q.front() < i - sub_len) {
                std::string tmp = s.substr(q.front(), words[0].size());
                _current[tmp]--;
                q.pop();
            }

            std::string current_string = s.substr(i, words[0].size());

            if (_origin.find(current_string) != _origin.end()) {
                //  清除多余元素
                while (_current[current_string] > _origin[current_string]) {
                    std::string tmp = s.substr(q.front(), words[0].size());
                    _current[tmp]--;
                    q.pop();
                }

                _current[current_string]++;
                q.push(i);

                if (q.size() == words.size()) {
                    if (check(_origin, _current, words)) {
                        int pos = q.front();
                        ans.push_back(pos);
                        _current.clear();
                        i = q.front() + 1;
                        q = std::queue<int>();
                    }
                    else {
                        i = i - sub_len + 1;
                        _current.clear();
                        q = std::queue<int>();
                    }
                } else
                    i += words[0].size();
            }

            // 不存在
            else {
                _current.clear();
                // 要注意，这个时候队列可能是空的
                i = i - sub_len + 1 >= 0 ? i - sub_len + 1 : i + 1;
                q = std::queue<int>();
            }
        }
        return ans;
    }

   private:
    bool check(Umap &a, Umap &b, std::vector<string> &words) {
        for (auto &si : words) {
            if (a[si] != b[si]) return false;
        }
        return true;
    }
};

int main() {
    Solution solution = Solution();
    std::string s = "ababaab";
    std::vector<std::string> arr = {"ab", "ba", "ba"};
    auto ans = solution.findSubstring(s, arr);
    for (auto ai : ans) {
        std::cout << ai << " ";
    }
}