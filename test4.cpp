#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <deque>
#include <iostream>
#include <memory>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#define For(i, j, n) for (int i = j; i <= n; ++i)
#ifdef DEBUG
#define DEBUG_LOG(fmt, ...)                  \
    do {                                     \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
    } while (0);
#else
#define DEBUG_LOG(fmt, ...) \
    do {                    \
    } while (0);
#endif

template <typename T>
inline T read() {
    T x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

using std::queue;
using std::shared_ptr;
using std::string;
using std::vector;

class Solution {
   public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* dummy = new ListNode(-1000, head);
        int cnt = 0;
        ListNode *cur = dummy, *prev = nullptr;
        while (cnt < left) {
            cnt++;
            prev = cur;
            cur = cur->next;
        }
        ListNode* left_bound = prev;
        // 再次移动
        cnt++;
        prev = cur;
        cur = cur->next;
        for (; cnt <= right; cnt++) {
            ListNode* tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp
        }
        left_bound->next->next = cur;
        left_bound->next = prev;
        return dummy->next;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
