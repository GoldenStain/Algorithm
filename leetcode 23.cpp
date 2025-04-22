// heap solution
class Solution {
private:
  struct Cmp {
    bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
  };

public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    std::priority_queue<ListNode *, std::vector<ListNode *>, Cmp> Q;
    ListNode *dummy = new ListNode();
    for (auto &li : lists) {
      // 小心空节点，如果不小心把nullptr放进堆里，就会导致我们的Cmp报错（因为空节点没有val）
      if (li)
        Q.push(li);
    }
    ListNode *st = dummy;
    while (Q.size()) {
      auto tmp = Q.top();
      st->next = tmp;
      Q.pop();
      // 小心空节点
      if (tmp->next)
        Q.push(tmp->next);
      st = st->next;
    }
    st->next = nullptr;
    return dummy->next;
  }
};

// divide and conquer solution
class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    int n = lists.size();
    return mergeLists(lists, 0, n - 1);
  }

private:
  ListNode *merge(ListNode *a, ListNode *b) {
    ListNode *dummy = new ListNode(-1), *st = dummy;
    while (a && b) {
      if (a->val <= b->val) {
        st->next = a;
        a = a->next;
      } else {
        st->next = b;
        b = b->next;
      }
      st = st->next;
    }
    if (a)
      st->next = a;
    if (b)
      st->next = b;
    return dummy->next;
  }

  ListNode *mergeLists(vector<ListNode *> &lists, int l, int r) {
    if (l == r)
      return lists[l];
    // 如果输入的vector为空，会直接到这里
    // 因此，也可以把这里的特判删掉，在入口函数特判一下vector的size是不是0
    if (l > r)
      return nullptr;
    int mid = (l + r) >> 1;
    return merge(mergeLists(lists, l, mid), mergeLists(lists, mid + 1, r));
  }
};
