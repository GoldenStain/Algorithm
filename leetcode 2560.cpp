// wrong DP
class Solution {
    public:
        int minCapability(vector<int>& nums, int k) {
            std::vector<int> sorted_n = nums;
            sort(sorted_n.begin(), sorted_n.end());
            int n = nums.size();
            int l = 0, r = n - 1;
    
            while (l < r) {
                int mid = (l + r) >> 1;
                // cout << l << " " << r << " " << mid << endl;
                if (check(nums, sorted_n[mid], k)) {
                    r = mid;
                } else
                    l = mid + 1;
            }
            return sorted_n[l];
        }
        bool check(vector<int>& nums, int x, int k) {
            std::vector<vector<int>> f(2, vector<int>{0, nums[0]}),
                g(2, vector<int>{0, 1});
            int idx, prev;
            for (int i = 1; i < nums.size(); i++) {
                idx = i & 1, prev = idx ^ 1;
                if (f[prev][1] >= f[prev][0]) {
                    g[idx][0] = g[prev][1];
                    f[idx][0] = f[prev][1];
                } else {
                    g[idx][0] = g[prev][0];
                    f[idx][0] = f[prev][1];
                }
                f[idx][1] = max(f[prev][0], nums[i]);
                g[idx][1] = g[prev][0] + 1;
                if (g[idx][0] >= k || g[idx][1] >= k)
                    break;
            }
            cout << "X: " << x << ": ";
            cout << f[idx][0] << " " << g[idx][0] << endl
                 << f[idx][1] << " " << g[idx][1] << endl;
            return (f[idx][0] <= x && g[idx][0] >= k) ||
                   (f[idx][1] <= x && g[idx][1] >= k);
        }
    };

// solution
class Solution {
    public:
        int minCapability(vector<int>& nums, int k) {
            std::vector<int> sorted_n = nums;
            sort(sorted_n.begin(), sorted_n.end());
            int n = nums.size();
            int l = 0, r = n - 1;
    
            while (l < r) {
                int mid = (l + r) >> 1;
                // cout << l << " " << r << " " << mid << endl;
                if (check(nums, sorted_n[mid], k)) {
                    r = mid;
                } else
                    l = mid + 1;
            }
            return sorted_n[l];
        }
        bool check(vector<int>& nums, int x, int k) {
            bool vis = false;
            int cnt = 0;
            for (int i = 0; i <nums.size(); i++) {
                if (!vis && x >= nums[i]) {
                    vis = true;
                    cnt++;
                    if (cnt >= k)
                        return true;
                }
                else
                    vis = false;
            }
            return false;
        }
    };