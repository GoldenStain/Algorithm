class Solution {
public:
    bool isPalindrome(string s) {
        int idx = 0;
        int n = s.size();
        for(int i = 0; i < n; i++)
            if (is_alpha(s[i]) || isdigit(s[i]))
                s[idx++] = s[i];
        s.erase(s.begin() + idx, s.end());
        int i = 0, j = idx - 1;
        while(i < j) {
            if (!is_euqal(s[i], s[j]))
                return false;
            i++;j--;
        }
        return true;
    }
    bool is_alpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }
    bool is_euqal(char a, char b) {
        if (a == b)
            return true;
        if (is_alpha(a) && is_alpha(b))
            return abs(a - b) == 32;
        return false;
    }
};