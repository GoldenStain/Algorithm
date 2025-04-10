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