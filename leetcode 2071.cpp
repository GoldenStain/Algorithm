class Solution {
  using VecI = std::vector<int>;

public:
  int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills,
                    int strength) {
    std::sort(tasks.begin(), tasks.end());     // tasks从小到大
    std::sort(workers.begin(), workers.end()); // workers从小到大
    int l = 0, r = std::min(tasks.size(), workers.size());
    while (l < r) {
      int mid = (l + r + 1) >> 1;
      if (check(tasks, workers, pills, strength, mid)) {
        l = mid;
      } else {
        r = mid - 1;
      }
    }
    return l;
  }

private:
  bool check(VecI &tasks, VecI &workers, int pills, int strength, int target) {
    // 而且如果我们把workers全放进来的话，我们只用一个线性结构就没法维护了
    // 就需要用到一个multiset
    // 所以我们换成一个双端队列，去线性地维护它
    std::deque<int> ws; // 从小到大
    // 这种静态构建ws的方法是错误的，在样例3的情况下会得到错解。
    // 只考虑最大的target个worker，以及最小的target个task
    // for (int i = workers.size() - target, j = target - 1; i < workers.size();
    // i++) {
    //   if (workers[i] + strength >= tasks[j]) {
    //     ws.push_back(workers[i]);
    //   }
    // }
    int _count = 0, now_worker = workers.size() - 1;
    // 因为我们的目标是完成targe个任务，所以只要考虑target个最小的任务就可以了
    for (int i = target - 1; i >= 0; i--) {
      // 把在吃了药以后，有资格胜任当前任务的worker都加进来
      while (now_worker >= 0 && workers[now_worker] + strength >= tasks[i]) {
        ws.push_front(workers[now_worker--]);
      }
      // 就算吃了药也没人能胜任
      if (ws.empty()) {
        return false;
      }
      // 不需要吃药
      if (ws.back() >= tasks[i]) {
        ws.pop_back();
        _count++;
      }
      // 需要吃药
      // 我们的入队方式决定了只有在吃药后能胜任任务的工人才会入队，所以可以直接用队头
      // 这个处理免去了使用有序集合带来的对数复杂度
      else {
        if (!pills)
          break;
        pills--;
        ws.pop_front();
        _count++;
      }
    }
    return (_count >= target);
  }
};