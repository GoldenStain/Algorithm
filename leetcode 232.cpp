class MyQueue {
public:
  MyQueue() {}

  void push(int x) { in_.push(x); }

  int pop() {
    if (out_.empty())
      convert_in2out();
    int ans = out_.top();
    out_.pop();
    return ans;
  }

  int peek() {
    if (out_.empty())
      convert_in2out();
    return out_.top();
  }

  bool empty() { return in_.empty() && out_.empty(); }

private:
  std::stack<int> in_, out_;
  void convert_in2out() {
    int n = in_.size();
    for (int i = 0; i < n; i++) {
      out_.push(in_.top());
      in_.pop();
    }
  }
};