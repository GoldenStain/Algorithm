class Solution {
    public:
        int romanToInt(string s) {
            int ans = 0;
            std::unordered_map<char, int> M;
    
            M['I'] = 1;
            M['V'] = 5;
            M['X'] = 10;
            M['L'] = 50;
            M['C'] = 100;
            M['D'] = 500;
            M['M'] = 1000;
    
            for(int i = 0; i < s.length(); i++) {
                int val = M[s[i]];
                if (i == s.length() - 1 || M[s[i]] >= M[s[i + 1]])
                    ans += val;
                else
                    ans -= val;
            }
            return ans;
        }
    };