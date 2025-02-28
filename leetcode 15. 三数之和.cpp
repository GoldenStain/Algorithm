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

// 双指针while写法
// 因为这里都是用while写的，所以所有的操作都要注意不能越界，要加上小于n的判断。
class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            std::sort(nums.begin(), nums.end());
            vector<vector<int>> ans;
            int n = nums.size();
            for(int i = 0; i <= n - 3; i++) {
                if (i && nums[i] == nums[i - 1])
                    continue;
                int j = i + 1, k = n - 1;
                while(j < k) {
                    // 注意不仅仅i需要判重，j也需要，而当i和j都判重之后，k作为剩下的那个数，就不需要判重了。
                    // 而且要加一个j > i + 1的条件，因为j == i + 1的时候，刚开始，这时候j和i相等是没问题的
                    while (j < n && j > i + 1 && nums[j] == nums[j - 1])
                        j++;
                    // 我们找i < j < k的三元组，如果相遇了就说明不再会出现这样的三元组了，可以结束了
                    // 类似于快排当中的if(i < j) swap(a[i], a[j]);
                    if (j >= k)
                        break;
                    int sum = nums[j] + nums[k];
                    if(sum == -nums[i]) {
                        ans.push_back({nums[i], nums[j], nums[k]});
                        j++; k--;
                    }
                    else if (sum < -nums[i])
                        j++;
                    else
                        k--;
                }
            }
            return ans;
        }
    };

// 双指针for写法，比while写法快一些