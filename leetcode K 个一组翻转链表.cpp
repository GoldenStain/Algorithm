class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (!head || !head->next)
      return head;
    int len = getLength(head);
    ListNode *dummy = new ListNode(-1, head);
    ListNode *precedor = dummy;
    int pos = 0;
    // 不包括pos自己，所以不用-1
    while (pos + k <= len) {
      oneReverse(precedor, 1, k);
      // 移动当前位置
      pos += k;
    }
    return dummy->next;
  }
  int getLength(ListNode *head) {
    int cnt = 0;
    while (head) {
      cnt++;
      head = head->next;
    }
    return cnt;
  }
  void oneReverse(ListNode *&precedor, int left, int right) {
    ListNode *cur = precedor->next, *prev = precedor;
    for (int cnt = left; cnt <= right; cnt++) {
      ListNode *tmp_next = cur->next;
      if (cnt > left) {
        cur->next = prev;
      }
      prev = cur;
      cur = tmp_next;
    }
    // 原来的第一个变成了最后一个，也是下一段的precedor
    ListNode *new_precedor = precedor->next;
    new_precedor->next = cur;
    // 最后一个变成第一个
    precedor->next = prev;
    // 更新precedor
    precedor = new_precedor;
  }
};

// recursive solution
class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    dummy->next = head;
    bool do_reverse = true;
    ListNode *left_node = dummy;
    while (do_reverse) {
      ListNode *st = left_node->next;
      ListNode *ed = left_node;
      for (int i = 1; i <= k; i++) {
        ed = ed->next;
        if (!ed) {
          // 先赋值再break，不然白赋值了
          do_reverse = false;
          break;
        }
      }
      if (!do_reverse)
        break;
      ed = ed->next;
      ListNode *reversedHead = reverseOneGroup(st, ed);
      left_node->next->next = ed;
      left_node->next = reversedHead;
      left_node = st;
    }
    return dummy->next;
  }

private:
  ListNode *dummy = new ListNode(-1);
  // 区间：[st, ed)
  ListNode *reverseOneGroup(ListNode *cur, ListNode *ed) {
    if (cur->next == ed) {
      return cur;
    }
    ListNode *reverseHead = reverseOneGroup(cur->next, ed);
    // 把next的next指向自己，进行翻转
    cur->next->next = cur;
    cur->next = nullptr;
    return reverseHead;
  }
};