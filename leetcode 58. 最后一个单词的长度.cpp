class Solution {
    public:
        int lengthOfLastWord(string s) {
            int n = s.size();
            int st = n - 1;
            while(st >= 0 && s[st] == ' ')
                st--;
            int ed = st;
            while(st >= 0 && s[st] != ' ')
                st--;
            return ed - st;
        }
    };