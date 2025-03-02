class Solution {
    public:
        int lengthOfLongestSubstring(string s) {
            int n = s.size();
            int m[200] = {0};
            std::deque<int> q;
            int ans = 0;
            for(int i = 0; i < n; i++) {
                q.push_back(i);
                m[s[i]]++;
                while(m[s[i]] > 1) {
                    m[s[q.front()]]--;
                    q.pop_front();
                }
                ans = std::max(ans, (int)q.size());
            }
            return ans;
        }
    };