#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
using namespace std;

class Solution {
    using Umap = std::unordered_map<std::string, int>;
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        std::unordered_map<std::string, int> _origin, _current;
        std::vector<int> ans;
        std::queue<int> q;
        for(auto &si: words) {
            _origin[si]++;
            _current[si] = 0;
        }
        // 起点
        int tot_len = words.size() * words[0].size(), sub_len = tot_len - words[0].size();
        for (int i = 0; i + words[0].size() <= s.size(); i++) {
            // 出队
            while (q.size() && q.front() < i - sub_len) {
                std::string tmp = s.substr(q.front(), words[0].size());
                _current[tmp]--;
                q.pop();
            }

            std::string current_string = s.substr(i, words[0].size());

            if (_origin.find(current_string) != _origin.end()) {
                //  清除多余元素
                while (_current[current_string] >= _origin[current_string]) {
                    std::string tmp = s.substr(q.front(), words[0].size());
                    _current[tmp]--;
                    q.pop();
                }

                _current[current_string]++;
                q.push(i);
                i += words[0].size() - 1;
                if(q.size() == words.size() && check(_origin, _current, words)) {
                    int pos= q.front();
                    ans.push_back(pos);
                    std::string first_string = s.substr(pos, words[0].size());
                    _current[first_string]--;
                    q.pop();
                }
            } 

            // 不存在
            else {
                _current.clear();
                q = std::queue<int>();
            }
        }
    return ans;
    }
private:
    bool check(Umap &a, Umap &b, vector<string> &words) {
        for (auto &si: words) {
            if (a[si] != b[si])
                return false;
        }
        return true;
    }
};

int main() {
    std::vector<string> arr = {"fooo","barr","wing","ding","wing"};
    string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    Solution solution;
    auto ans = solution.findSubstring(s, arr);
    for (auto ai:ans)
        std::cout << ai << " ";
}