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

// solution 2
class Solution {
    public:
        // 枚举1
        bool find132pattern(vector<int>& nums) {
            // 题解说“如果我们从左到右枚举 1 的下标 i，那么 j,k 的下标范围都是减少的，这样就不利于对它们进行维护。因此我们可以考虑从右到左枚举 i”我的理解是，如果i从左边开始，那么我们需要先求出完整的j和k集合，然后再一步一步地缩小它，这样更不好维护；如果i从右边开始，那么j和k的可选范围都是增加的，这有利于我们维护；回看枚举2的解法，我们枚举i，j和k一个正向增长，一个逆向增长，那无论我们从左还是从右开始，都是这种局面，那也就无所谓从哪边开始了。
            // 我们用单调栈来维护2，每次有新元素的时候，可以直接把单调栈内部所有小于该元素的值都弹出，因为2越大，越能容纳可能的1；弹出的过程中，更新一下最大的2 max_candidate的值；
            // 这里隐含了一个条件： 只要我们的max_candidate不再是初始值，就说明：
            // 我们已经通过上面的操作更新过单调栈了，也就意味着已经有满足3, 2条件的数对了（新元素对应3，被弹出的元素对应2）
            int max_candidate = INT_MIN;
            int n = nums.size();
            std::stack<int> stk;
            stk.push(nums[n - 1]);
            for (int i = n - 2; i >= 0; i--) {
                // 利用隐含条件判断，是否已经出现了解
                if (nums[i] < max_candidate)
                    return true;
                // 小坑，等于nums[i]的不能出栈，因为nums[i]不大于栈顶，就不能构成3 2 ，就没法更新答案
                while(stk.size() && stk.top() < nums[i])
                    max_candidate = std::max(max_candidate, stk.top()), stk.pop();
                // 小优化，如果nums[i]没法更新max_candidate，那加进来也没意义，可以直接跳过
                if (nums[i] > max_candidate)
                    stk.push(nums[i]);
            }
            return false;
        }
    };

// solution 3
class Solution {
    public:
        // 枚举2
        bool find132pattern(vector<int>& nums) {
            int n = nums.size();
            if (n < 3)
                return false;
            std::vector<int> stk_1, stk_3;
            stk_1.push_back(nums[0]);
            stk_3.push_back(nums[0]);
            for (int i = 1; i < n; i++) {
                if (i > 1) {
                    // check
                    auto it_1 = upper_bound(stk_1.begin(), stk_1.end(), nums[i], greater<int>()), 
                    it_3 = lower_bound(stk_3.begin(), stk_3.end(), nums[i], greater<int>()) - 1;
                    if (it_1 != stk_1.end()&&it_3 != stk_3.end()) {
                        // 一开始我有这样的顾虑：
                        // idx(it_1) == idx(it_3)的时候会不会误判？ 毕竟有可能这俩都是某个之前的nums[i]
                        // 不过我们一开始二分的时候，找到一个是<nums[i], 一个是<=nums[i]
                        // 所以他俩是不可能相等的， 因此这里要用<=  如果用<  可能会错过解
                        if ((it_1 - stk_1.begin()) <= (it_3 - stk_3.begin()))
                            return true;
                    }
                }
                // update stacks
                // 有可能取代现在的1   也有可能是新的2
                // 每次访问容器顶部的时候都要注意容器是不是空的，这里可以
                // 1. 加一个且条件
                // 2. 我们在一开始先把nums[0]加进来，保证栈不会为空。
                if (nums[i] < stk_1.back()) {
                    stk_1.push_back(nums[i]);
                    stk_3.push_back(nums[i]);
                }
                else if (nums[i] > stk_3.back()) {
                    int tmp = stk_1.back();
                    // 两个栈的size是同步的
                    while(stk_3.size() && nums[i] > stk_3.back()) {
                        stk_1.pop_back();
                        stk_3.pop_back();
                    }
                    stk_1.push_back(tmp);
                    stk_3.push_back(nums[i]);
                }
            }
            return false;
        }
    };