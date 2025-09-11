class MedianFinder {
public:
  MedianFinder() {}

  void addNum(int num) {
    if (left.size() == right.size()) {
      right.push(num);
      left.push(right.top());
      right.pop();
    } else {
      left.push(num);
      right.push(left.top());
      left.pop();
    }
  }

  double findMedian() {
    if (left.size() == right.size())
      return (left.top() * 1.0 + right.top()) / 2;
    return left.top();
  }

private:
  std::priority_queue<int, vector<int>, std::greater<>> left;
  std::priority_queue<int, vector<int>, std::less<>> right;
};