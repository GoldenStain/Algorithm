#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#define R(x) x = read()
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;
inline int read() {
    int x = 0, f = 1;
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

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head) 
            return head;
        int n = get_len(head);
        ListNode *dummy = new ListNode(-1, head), *cur = dummy;
        for(int now = 0; now + k <= n; now += k) {
            cur = onceReverse(cur, k);
        }
        return dummy->next;
    }

   private:
    int get_len(ListNode* head) {
        int n = 0;
        while(head) {
            n++;
            head = head->next;
        }
        return n;
    }
    ListNode* onceReverse(ListNode* d, int k) {
        ListNode *cur = d, *prev = nullptr;
        for(int i = 0; i <= k; i++) {
            ListNode *_next = cur->next;
            if (i > 1) {
                cur->next = prev;
            }
            prev = cur;
            cur = _next;
        }
        return prev;
    }
};

int main() {
    int q = -5 / 3, r = -5 % 3;
    std::cout << q << " " << r << std::endl;
    return 0;
}