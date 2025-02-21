class Solution {
    public:
        using VecInt = vector<int>;
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            vector<VecInt> ans;
            int st = -1, ed = -1;
            sort(intervals.begin(), intervals.end(), cmp);
            int n = intervals.size();
            for(int i = 0; i < n; i++) {
                if (intervals[i][0] > ed) {
                    if (i) 
                        ans.emplace_back(vector<int>{st, ed});
                    st = intervals[i][0];
                    ed = intervals[i][1];
                }
                else
                    ed = max(ed, intervals[i][1]);
            }
            if (st != -1)
                ans.emplace_back(vector<int>{st, ed});
            return ans;
        }
        static bool cmp(VecInt &a, VecInt &b) {
            return a[0] < b[0];
        }
    };

// no special judge
class Solution {
    public:
        using VecInt = vector<int>;
        vector<vector<int>> merge(vector<vector<int>>& intervals) {
            vector<VecInt> ans;
            sort(intervals.begin(), intervals.end(), cmp);
            int n = intervals.size();
            for(int i = 0; i < n; i++) {
                int j = i + 1, ed = intervals[i][1];
                while (j < n && intervals[j][0] <= ed) {
                    ed = max(ed, intervals[j][1]);
                    j++;
                }
                j--;
                ans.push_back(VecInt{intervals[i][0], ed});
                i = j;
            }
            return ans;
        }
        static bool cmp(VecInt &a, VecInt &b) {
            return a[0] < b[0];
        }
    };