class Solution {
   public:
    static constexpr int L = 1e6;
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (nums[i] <= 0) {
                nums[i] = L;
            }  // 先排除负数的干扰
        }
        for (int i = 0; i < n; i++) {
            int x = std::abs(nums[i]);
            if (x <= n) {
                nums[x - 1] = -std::abs(nums[x - 1]);
            }
        }
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) return i + 1;
        }
        return n + 1;
    }
};

// perfect solution
class Solution {
    public:
     int firstMissingPositive(vector<int>& nums) {
         int n = nums.size();
         for (int i = 0; i < n; i++) {
             while (nums[i] != i + 1) {
                 if (nums[i] <= 0 || nums[i] > n || nums[i] == nums[nums[i] - 1])
                     break;
                 // 这些值在1~N的合法序列中没有一席之地，可以break了。
                 // 交换无效，也可以break了；这个case一开始没有想到，是对着没通过的样例观察才发现的。
                 // 因为我们的输入可能会有重复数字，不加上这个判断就会死循环
                 // 而这个判断的正确性： 假如当前位置和目标位置已经相等了，那无论继续交换多少次，都不会改变序列了，所以能够在这里直接停止。
                 std::swap(nums[i], nums[nums[i] - 1]);
             }
         }
         for (int i = 0; i < n; i++)
             if (nums[i] != i + 1) return i + 1;
         return n + 1;
     }
 };