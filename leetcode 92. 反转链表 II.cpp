/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int left, int right) {
    if (!head)
      return head;
    ListNode *dummy = new ListNode(0, head);
    int cnt = 0;
    ListNode *now, *prev;
    ListNode *p;
    for (now = dummy, prev = nullptr; cnt <= right; cnt++) {
      ListNode *_next = now->next;
      if (cnt == left - 1)
        p = now;
      if (cnt > left && cnt <= right) {
        now->next = prev;
      }
      // finally
      prev = now;
      now = _next;
    }
    // 如果是翻转整个链表的话，最后now会移动到nullptr，那么p->next->next =
    // now，就会保证新链表能走到nullptr
    // 比如1->2->3->4，整个翻转，最后我们需要把1的next设置成nullptr，这个操作由p->next->next
    // = now;完成
    p->next->next = now;
    p->next = prev;
    return dummy->next;
  }
};

// recursive solution
class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int left, int right) {
    ListNode *dummy = new ListNode(-1, head), *cur = dummy;
    ListNode *st, *ed, *left_bound = dummy;
    for (int i = 1; i <= right; i++) {
      cur = cur->next;
      if (i == left - 1) {
        left_bound = cur;
      }
      if (i == left)
        st = cur;
    }
    ed = cur->next;
    ListNode *newHead = reverseRange(st, ed);
    left_bound->next->next = ed;
    left_bound->next = newHead;
    return dummy->next;
  }

private:
  ListNode *reverseRange(ListNode *cur, ListNode *ed) {
    if (cur == ed || cur->next == ed)
      return cur;
    ListNode *newHead = reverseRange(cur->next, ed);
    cur->next->next = cur;
    cur->next = nullptr;
    return newHead;
  }
};