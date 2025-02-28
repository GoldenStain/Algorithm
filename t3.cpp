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

int n, P = 10000;
int t[10000], b[10000], s[10000];

int main() {
    n=read();
    int ans = 0;
	for(int i=1;i<=n;i++) t[read()]++;
	for(int i=1;i<=P;i++) if(t[i])
	{
		for(int j=i*2;j<=P;j+=i) if(t[j])
			b[i]+=t[j],s[j]+=t[i];
		b[i]+=t[i]-1,s[i]+=t[i]-1;
		ans+=t[i]*b[i];
        std::cout << "I: " << i << " " << b[i] << " " << s[i] << std::endl;
	}
    std::cout << ans << std::endl;
    return 0;
}