// slow way
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            auto myHash = [fn = hash<int>{}](const vector<int> &arr) ->size_t {
                return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                    return (acc << 1) ^ fn(num);
                });
            };
            unordered_set<vector<int>, decltype(myHash)> S(0, myHash);
            int n = nums.size();
            vector<vector<int>> ans;
            sort(nums.begin(), nums.end());
            for(int k = 0; k < n; k++) {
                int i = k + 1, j = n - 1;
                while(i < j) {
                    int t = nums[i] + nums[j];
                    if (t == -nums[k]) {
                        auto tmp = vector<int>{nums[k], nums[i], nums[j]};
                        if(S.count(tmp) == 0)
                            ans.emplace_back(tmp), S.insert(tmp);
                        i++;j--;
                    }
                    else if (t > -nums[k])
                        j--;
                    else
                        i++;
                }
            }
            return ans;
        }
    };