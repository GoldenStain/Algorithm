// solution 1
class Solution {
    public:
        // 枚举3
        bool find132pattern(vector<int>& nums) {
            int n = nums.size();
            // corner case
            if (n < 3)
                return false;
            int min_v = nums[0];
            std::multiset<int> S;
            for(int j = n - 1; j >= 2; j--) {
                S.insert(nums[j]);
            }
            for(int k = 1; k < n - 1; k++) {
                if (nums[k] > min_v) {
                    auto candidate = S.upper_bound(min_v);
                    if (candidate!= S.end()&& nums[k] > *candidate)
                        return true;
                }
                // finally
                min_v = std::min(min_v, nums[k]);
                // 在k这里，我们用的是k+1 ~ n-1 范围内的数字，我们k要往后移动了，那我们查找的区间也要相应地向后收缩。
                S.erase(S.find(nums[k +1]));
            }
            return false;
        }
    };