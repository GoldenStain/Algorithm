class Solution {
public:
  int calculate(string s) {
    // 主循环
    for (int i = 0; i < s.size(); i++) {
      if (s[i] == ' ')
        continue;
      if (std::isdigit(s[i])) {
        prev_is_parenthese = false;
        int j = i;
        int number = 0;
        while (j < s.size() && std::isdigit(s[j])) {
          number = number * 10 + (s[j] - '0');
          j++;
        }
        // 这里数字之间不一定有空格隔开，所以i只能移动到j-1而不是j
        i = j - 1;
        nums.push_back(number);
      } else if (s[i] == '(') {
        prev_is_parenthese = true;
        op.push_back(s[i]);
      } else if (s[i] == ')') {
        prev_is_parenthese = false;
        while (op.back() != '(') {
          eval();
        }
        // 把左括号去掉
        op.pop_back();
      } else {
        // 注意区别负号和减号
        if (s[i] == '-' && prev_is_parenthese)
          nums.push_back(0);
        // 先使用，再更新
        // 这里因为数字和符号的先后顺序问题，只在数字的if里面设为false也没问题，但是这样写更万无一失，更直观
        prev_is_parenthese = false;
        while (op.size() && _priority[op.back()] >= _priority[s[i]]) {
          eval();
        }
        op.push_back(s[i]);
      }
    }
    while (op.size())
      eval();
    return nums.back();
  }

private:
  std::vector<char> op;
  std::vector<int> nums;
  bool prev_is_parenthese = true;
  std::unordered_map<char, int> _priority = {
      {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
  void eval() {
    int res;
    char Op = op.back();
    op.pop_back();
    int b = nums.back();
    nums.pop_back();
    int a = nums.back();
    nums.pop_back();
    switch (Op) {
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
    }
    nums.push_back(res);
  }
};