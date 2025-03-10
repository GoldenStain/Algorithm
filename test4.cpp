#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

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

// Definition for a Node.
class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
   public:
    Node* connect(Node* root) {
        if (!root) return root;
        // next_start表示下一层要从哪里开始，也就是下一层最左边的节点。
        Node* start = root;
        while (start) {
            Node* cur = start;
            Node *prev = NULL, *next_start = NULL;
            while (cur) {
                if (cur->left) {
                    if (prev) prev->next = cur->left;
                    prev = cur->left;
                    if (!next_start) next_start = cur->left;
                }
                if (cur->right) {
                    if (prev) prev->next = cur->right;
                    prev = cur->right;
                    if (!next_start) next_start = cur->right;
                }
                cur = cur->next;
            }
            start = next_start;
        }
        return root;
    }
};

int main() { return 0; }
