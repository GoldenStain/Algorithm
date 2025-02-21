class Solution {
    public:
        using VecInt = vector<int>;
        vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
            auto pos = lower_bound(intervals.begin(), intervals.end(), newInterval[0], cmp);
            int ipos = pos - intervals.begin();
            ipos = ipos?ipos-1:ipos;
            intervals.insert(pos, newInterval);
            int st = intervals[ipos][0], ed = intervals[ipos][1];
            for(auto it = intervals.begin() + ipos; it != intervals.end(); it++) {
                auto tmp = *it;
                if (tmp[0] > ed) {
                    intervals[ipos++] = VecInt{st, ed};
                    st = tmp[0];
                    ed = tmp[1];
                }
                else
                    ed = max(ed, tmp[1]);
            }
            intervals[ipos++] = VecInt{st, ed};
            intervals.erase(ipos + intervals.begin(), intervals.end());
            return intervals;
        }
        static bool cmp(const VecInt &ele, int target) {
            return ele[0] < target;
        }
    };