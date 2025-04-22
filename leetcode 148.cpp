class Solution {
public:
  ListNode *sortList(ListNode *head) {
    if (!head || !head->next) {
      return head;
    }
    ListNode *dummy = new ListNode(-1, head);
    int totalLength = getLength(head);
    // 每次都合并两条短的，把它们变有序，得到更长的有序序列
    // 比交换节点更安全，也更好写
    for (int curLength = 1; curLength < totalLength; curLength <<= 1) {
      // 排序之后head的位置可能发生变化，所以这里不能用head，要用dummy->next
      ListNode *cur = dummy->next, *leftBound = dummy;
      // 不需要用一个int记录cur的位置
      // 因为这道题不同于K个一组翻转链表
      // 最后长度不及K个就不操作了
      // 这道题最后长度不够的部分也要排序
      // 所以cur一直移动到最后就行
      while (cur) {
        ListNode *firstList = cur;
        // 这里不需要 && cur，可以直接&& cur->next
        for (int i = 1; i < curLength && cur->next; i++) {
          cur = cur->next;
        }
        ListNode *nextCur = cur->next, *secondList = nextCur;
        cur->next =
            nullptr; // 合并链表的时候，传入的链表需要末尾是nullptr，所以这里我们手动把链表断开
        cur = nextCur;
        for (int i = 1; i < curLength && cur && cur->next; i++) {
          cur = cur->next;
        }
        // 这里的nextCur已经被用过，先前的值是一个“脏值”，我们要先给它复原
        // 也可以前面不定义nextCur，到了这一步再定义，并赋初值
        nextCur = nullptr;
        // 这里有可能cur已经移动到nullptr了，所以需要用if防止越界
        // 讲课：把这个if去掉，观察现象
        if (cur) {
          nextCur = cur->next;
          cur->next = nullptr;
        }
        // 这里第一个参数不能用leftBound->next,这时候链表还没连起来，必须用firstList
        leftBound->next = mergeLists(firstList, secondList);
        // 因为排序之后cur的位置变了，我们不能用leftBound =
        // cur的方式来移动leftBound,只能通过循环，把leftBound一步一步地往后移
        while (leftBound->next) {
          leftBound = leftBound->next;
        }
        // 我们前面通过cur->next = nullptr把链表断开了，这里为什么不用恢复呢？
        // 分析一下能够发现，leftBound->next = mergeLists(leftBound->next,
        // secondList); 不仅进行了排序，也完成了恢复工作
        // 每次leftBound的位置，都是在待排序位置的前一个，相当于一个动态的dummy
        cur = nextCur;
      }
    }
    return dummy->next;
  }
  inline int getLength(ListNode *head) {
    int cnt = 0;
    while (head) {
      cnt++;
      head = head->next;
    }
    return cnt;
  }

  inline ListNode *mergeLists(ListNode *l1, ListNode *l2) {
    ListNode *dummy = new ListNode(-1), *returnedDummy = dummy;
    while (l1 && l2) {
      if (l1->val <= l2->val) {
        dummy->next = l1;
        l1 = l1->next;
      } else {
        dummy->next = l2;
        l2 = l2->next;
      }
      dummy = dummy->next;
    }
    if (l1)
      dummy->next = l1;
    if (l2)
      dummy->next = l2;
    return returnedDummy->next;
  }
};

// mergeSort solution
class Solution {
public:
  ListNode *sortList(ListNode *head) {
    if (!head || !head->next)
      return head;
    return mergeSort(head, nullptr);
  }

private:
  // [head, tail) 左闭右开区间
  ListNode *mergeSort(ListNode *head, ListNode *tail) {
    if (head == tail)
      return nullptr;
    // 只有一个节点的话，我们手动把这个部分摘出来变成一个单独的链表
    // 因为合并链表算法要求输入的链表结尾都是nullptr
    // 这个操作在经过递归合并之后，可以保证参与操作的所有链表，其结尾都是nullptr
    if (head->next == tail) {
      head->next = nullptr;
      return head;
    }
    ListNode *mid = findMid(head, tail); // 后半部分第一个点
    return merge(mergeSort(head, mid), mergeSort(mid, tail));
  }
  inline ListNode *findMid(ListNode *head, ListNode *tail) {
    ListNode *slow = head, *fast = head;
    while (fast != tail && fast->next != tail) {
      fast = fast->next->next;
      slow = slow->next;
    }
    return slow;
  }
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
};