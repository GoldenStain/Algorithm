#include <iostream>
#include <stack>
#include <unordered_map>

class Solution {
    using string = std::string;

   public:
    int calculate(string s) {
        for (int i = 0; i < s.length(); i++) {
            if (s[i] == ' ') continue;
            if (isdigit(s[i])) {
                last_is_parenthesis = false;
                int j, res = 0;
                for (j = i; isdigit(s[j]); j++) {
                    res = res * 10 + (s[j] - '0');
                }
                i = j - 1;
                num.push(res);
            } else {
                if (s[i] == '(') {
                    last_is_parenthesis = true;
                    op.push('(');
                }
                else if (s[i] == ')') {
                    while (op.top() != '(') eval();
                    op.pop();
                } else {
                    if (s[i] == '-' && last_is_parenthesis) {
                        num.push(0);
                    }
                    while (op.size() && _priority[op.top()] >= _priority[s[i]])
                        eval();

                    op.push(s[i]);
                }
            }
        }
        while (op.size()) eval();
        return num.top();
    }

   private:
    std::stack<int> num;
    std::stack<char> op;
    bool last_is_parenthesis = true;
    std::unordered_map<char, int> _priority = {
        {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    void eval() {
        int b = num.top();
        num.pop();
        int a = num.top();
        num.pop();
        char _operator = op.top();
        op.pop();
        int res;
        if (_operator == '+') {
            res = a + b;
        } else if (_operator == '-') {
            res = a - b;
        } else if (_operator == '*')
            res = a * b;
        else
            res = a / b;
        // std::cout << a << " " << _operator << " " << b << " = " << res
        //           << std::endl;
        num.push(res);
    }
};