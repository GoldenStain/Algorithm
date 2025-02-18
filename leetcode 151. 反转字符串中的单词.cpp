// 空间复杂O(n) 
class Solution {
    public:
        string reverseWords(string s) {
            std::stack<string> stk;
            for(int i = 0; i < s.size(); i++) {
                if (s[i] == ' ')
                    continue;
                int ed = i;
                while(ed < s.size() && s[ed] != ' ')
                    ed++;
                stk.push(s.substr(i, ed - i));
                i = ed;
            }
            std::string ans = "";
            while(stk.size()) {
                ans += stk.top();
                stk.pop();
                if (stk.size())
                    ans += " ";
            }
            return ans;
        }
    };

// python秒杀

class Solution:
    def reverseWords(self, s: str) -> str:
        return " ".join(reversed(s.split()))        

// 空间复杂度O(1)的错误写法

class Solution {
    public:
        string reverseWords(string s) {
            reverse(s.begin(), s.end());
            int n = s.size(), st = 0;
            while(s[st] == ' ')
                st++;
            for(int i = st; i < n; i++) {
                if (s[i] == ' ')
                    continue;
                int ed = i;
                while(ed < n && s[ed] != ' ')
                    ed++;
                reverse(s.begin() + i, s.begin() + ed);
                i = ed;
            }
            int ed = n - 1;
            while(s[ed] == ' ')
                ed--;
            return s.substr(st, ed - st + 1);
        }
    };

// 空间复杂度O(1)正解

class Solution {
    public:
        string reverseWords(string s) {
            reverse(s.begin(), s.end());
            int n = s.size(), idx = 0;
            for(int i = 0; i < n; i++) {
                if (s[i] == ' ')
                    continue;
                if (idx)
                    s[idx++] = ' ';
                int ed = i;
                while(ed < n && s[ed] != ' ') {
                    s[idx++] = s[ed++];
                }
                reverse(s.begin() + idx - ed + i, s.begin() + idx);
                i = ed;
            }
            s.erase(s.begin() + idx, s.end());
            return s;
        }
    };