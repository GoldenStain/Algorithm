class Solution {
public:
  ListNode *quickSortList(ListNode *head) {
    if (!head || !head->next)
      return head;
    quickSort(head, nullptr);
    return head;
  }
  // 对[head, tail)区间进行排序
  void quickSort(ListNode *head, ListNode *tail) {
    if (head == tail)
      return;
    ListNode *p = head, *q = p->next;
    // (head, p]都是小于head->val的，(p, q]都是大于等于的
    while (q != tail) {
      if (q->val < head->val) {
        p = p->next;
        std::swap(p->val, q->val);
      }
      q = q->next;
    }
    // 如果head和p不在同一个点，把head的值放到p上，即把哨兵放到p，那么,[head,
    // p)<pivot, (p, tail)>=pivot，下次排序就不用考虑p，区间就缩小了
    if (head != p)
      std::swap(head->val, p->val);
    quickSort(head, p);
    quickSort(p->next, tail);
  }
};