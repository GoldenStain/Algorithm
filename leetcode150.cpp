#include <iostream>
#include <stack>
#include <string>
#include <vector>

class Solution {
   public:
    int evalRPN(std::vector<std::string> &tokens) {
        for (auto token : tokens) {
            if (!is_op(token)) {
                int operand = to_digit(token);
                stk.push(operand);
            } else {
                int res, a, b;
                b = stk.top();
                stk.pop();
                a = stk.top();
                stk.pop();
                switch (token[0]) {
                    case '+':
                        res = a + b;
                        break;
                    case '-':
                        res = a - b;
                        break;
                    case '*':
                        res = a * b;
                        break;
                    case '/':
                        res = a / b;
                        break;
                    default:
                        break;
                }
                stk.push(res);
            }
        }
        return stk.top();
    }

   private:
    bool is_op(std::string &s) {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }
    int to_digit(std::string &s) {
        int res = 0, f = 1;
        for (auto i : s) {
            if (i == '-')
                f = -1;
            else
                res = res * 10 + i - '0';
        }
        return res * f;
    }
    std::stack<int> stk;
};