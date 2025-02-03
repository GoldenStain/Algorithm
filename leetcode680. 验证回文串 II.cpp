class Solution {
public:
    bool validPalindrome(string s) {
        return checkSubString(s, 0, s.length() - 1, 0) <= 1;
    }
private:
    int checkSubString(string &s, int l, int r, int cnt) {
        int res1 = 1e6, res2 = 1e6;
        if (cnt > 1)
            return 1e6;
        if (l >= r) {
            return cnt;
        }
        while (l < r && s[l] == s[r])
            l++, r--;
        if (l >= r)
            return cnt;
        if (s[l + 1] == s[r])
            res1 = checkSubString(s, l + 1, r, cnt + 1);
        if (s[l] == s[r - 1])
            res2 = checkSubString(s, l, r - 1, cnt + 1) ;
        return min(res2, res1);
    }
};

// 一开始的错误做法
class Solution {
public:
    bool validPalindrome(string s) {
        int i = 0, j = s.length();
        int cnt = 0;
        while( i < j) {
            if (s[i] == s[j])
                i++, j--;
            else if (s[j-1] == s[i])
                j--, cnt++;
            else if (s[i+1] == s[j])
                i++, cnt++;
            else return false;
            if (cnt > 1)
                return false;
        }
        return true;
    }
};