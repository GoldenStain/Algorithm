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
