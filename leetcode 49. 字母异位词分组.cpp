// slow way
class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            unordered_map<string, vector<string>> M;
            for(auto &si: strs) {
                string v = si;
                sort(si.begin(), si.end());
                M[si].emplace_back(v);
            }
            vector<vector<string>> ans;
            for(auto &pi: M) {
                ans.emplace_back(pi.second);
            }
            return ans;
        }
    };

// fast way
class Solution {
    public:
        vector<vector<string>> groupAnagrams(vector<string>& strs) {
            auto arrayHash = [fn = hash<int>{}](const array<int, 26>& arr) -> size_t {
                return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                    return (acc << 1) ^ fn(num);
                });
            };
            unordered_map<array<int,26>, vector<string>, decltype(arrayHash)> M(0, arrayHash);
            for(auto it = strs.begin(); it != strs.end(); it++) {
                array<int, 26> tmp{};
                for(size_t i = 0; i < it->size(); i++) 
                    tmp[(*it)[i] - 'a']++;
                M[tmp].emplace_back(*it);
            }
            vector<vector<string>> ans;
            for(auto &mi: M) {
                ans.emplace_back(mi.second);
            }
            return ans;
        }
    };