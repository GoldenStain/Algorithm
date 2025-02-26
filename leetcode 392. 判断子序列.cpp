class Solution {
    public:
        bool isSubsequence(string s, string t) {
            int n = s.size(), m = t.size();
            int i = 0, j = 0;
            while(j < m && i < n) {
                if (t[j] == s[i])
                    i++;
                j++;
            }
            if (i == n)
                return true;
            return false;
        }
    };