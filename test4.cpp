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
    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) {
            return nullptr;
        }
        return buildTree(head, nullptr);
    }
    // [left, right) 区间
    TreeNode *buildTree(ListNode *left, ListNode *right) {
        if (left == right) {
            return nullptr;
        }
        ListNode *mid = getMid(left, right);
        TreeNode *now = new TreeNode(mid->val);
        now->left = buildTree(left, mid);
        now->right = buildTree(mid->next, right);
        return now;
    }
    ListNode *getMid(ListNode *left, ListNode *right) {
        ListNode *slow = left, *fast = left;
        while(fast != right && fast->next != right) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main() {
    string s;
    std::cout << s.size() << std::endl;
    return 0;
}
