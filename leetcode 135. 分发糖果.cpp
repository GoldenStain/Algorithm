// my solution
class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    if (n == 1)
      return 1;
    std::vector<int> candys(n, 0);
    using PII = pair<int, int>;
    priority_queue<PII, std::vector<PII>, std::greater<PII>> q;
    for (int i = 0; i < n; i++) {
      q.push({ratings[i], i});
    }
    int ans = 0;
    while (q.size()) {
      PII t = q.top();
      q.pop();
      int pos = t.second, t1, t2;
      // printf("pos: %d", pos);
      if (t.second == 0)
        t1 = t2 = 1;
      else if (t.second == n - 1)
        t1 = t2 = pos - 1;
      else {
        t1 = pos - 1;
        t2 = pos + 1;
      }
      t1 = ratings[pos] > ratings[t1] ? candys[t1] + 1 : 1;
      t2 = ratings[pos] > ratings[t2] ? candys[t2] + 1 : 1;
      candys[pos] = max(t1, t2);
      candys[pos] = candys[pos] == 0 ? 1 : candys[pos];
      // printf("t1 : %d, t2: %d, candys: %d\n", t1, t2, candys[pos]);
      ans += candys[pos];
    }
    return ans;
  }
};

// O(2n) solution
class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    vector from_left(n, 1), from_right(n, 1);
    int res = 0;
    for (int i = 1; i < n; i++) {
      from_left[i] =
          (ratings[i] <= ratings[i - 1]) ? (1) : (from_left[i - 1] + 1);
    }
    res += std::max(from_left[n - 1], from_right[n - 1]);
    for (int i = n - 2; i >= 0; i--) {
      from_right[i] =
          (ratings[i] <= ratings[i + 1]) ? (1) : (from_right[i + 1] + 1);
      res += std::max(from_left[i], from_right[i]);
    }
    return res;
  }
};

// O(n) solution
// 上升的时候每次加pre只统计当前位置的贡献；下降的时候加pre，会统计这一整段下降序列这一步的贡献
class Solution {
public:
  int candy(vector<int> &ratings) {
    int n = ratings.size();
    int inc = 1, dec = 0, pre = 1, res = 1;
    // 下标为0的同学，我们直接分配1就行，默认归类为递增当中
    // 从等于和大于的两种case提取相同逻辑再合并，就是官方解法
    for (int i = 1; i < n; i++) {
      if (ratings[i] == ratings[i - 1]) {
        inc = pre = 1;
        dec = 0;
        res += pre;
      } else if (ratings[i] > ratings[i - 1]) {
        // 注意这里不能是：inc++;然后再pre=inc;
        // 因为我们在递减的case里面，不重置inc，只重置pre（需要保留上一段递增的长度，来执行84行逻辑
        // 这时候的inc等于上一段递增长度，如果拿inc++，那么就会接着上一段递增继续增加
        // 这时候的pre是最新的，基于上一个位置
        // 所以我们要先pre++;然后基于pre去更新inc
        pre++;
        dec = 0;
        inc = pre;
        res += pre;
      } else {
        dec++;
        // 如果dec长度和inc相等，那么上一个inc的峰值就不够用了，要被迫给峰值+1，相当于把上段序列最后一个成员分配给递减序列
        if (dec == inc) {
          dec++;
        }
        pre = 1;
        // 新增的这个同学分配一个糖果，而上一个同学默认也是一个糖果，为了保持序列合法性，上一个同学需要加一个糖果，然后上上个同学也要加...
        // 因此答案会增加dec（1 + old_dec == now_dec）
        res += dec;
      }
    }
    return res;
  }
};