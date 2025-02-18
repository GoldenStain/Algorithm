class Solution {
    public:
        string longestCommonPrefix(vector<string>& strs) {
            int ans_pos = 0, n = strs.size();
            while(true) {
                bool flag = false;
                char c = ' ';
                for(int i = 0; i < n; i++) {
                    if (ans_pos >= strs[i].size()) {
                        flag = true;
                        break;
                    }
                    if (i == 0)
                        c = strs[i][ans_pos];
                    else if (strs[i][ans_pos] != c) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    break;
                ans_pos++;
            }
            if (!ans_pos)   return "";
            return strs[0].substr(0, ans_pos);
        }
    };