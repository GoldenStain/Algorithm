#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <string.h>
#include <cstring>
const double pi = acos(-1.0), eps = 1e-6;
double S;

struct ListNode;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
   public:
    const int N = 100005;
    ListNode *detectCycle_1(ListNode *head) {
        ListNode *fast = head, *slow = head;
        bool hasCycle = false;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                hasCycle = true;
                break;
            }
        }
        if (!hasCycle) {
            return nullptr;
        }
        ListNode *newStart = slow;  //	新的起点
        slow = head;
        while (newStart != slow) {
            slow = slow->next;
            newStart = newStart->next;
        }
        return slow;
    }

    ListNode *detectCycle(ListNode *head) {
        ListNode *cur = head;
        while (cur) {
            if (cur->val == N) {
                return cur;
            }
            cur->val = N;
            cur = cur->next;
        }
        return cur;
    }

    ListNode *oddEvenList_1(ListNode *head) {
        if (!head) {
            return head;
        }
        ListNode *cur = nullptr, *headofOdd = head,
                 *headofEven = head->next ? head->next : nullptr;
        if (!headofEven) {
            return head;
        }
        ListNode *odd = headofOdd, *even = headofEven;
        cur = head->next->next;
        odd->next = even->next = nullptr;
        if (!cur) {
            odd->next = headofEven;
            return headofOdd;
        }
        int cnt = 3;
        while (cur) {
            std::cout << cur->val << std::endl;
            if (cnt & 1) {
                odd->next = cur;
                odd = cur;
            }  //	奇数
            else {
                even->next = cur;
                even = cur;
            }
            cnt++;
            cur = cur->next;
            // 这两处记得把连接切断，否则会死循环
            odd->next = nullptr;
            even->next = nullptr;
        }
        odd->next = headofEven;
        return headofOdd;
    }

    ListNode *oddEvenList(ListNode *head) {
        // 如果是空的或者只有一个点，就不用翻转了
        if (!head || !head->next) {
            return head;
        }
        auto cur = head, oddHead = cur, oddTail = cur;
        auto evenHead = cur->next, evenTail = evenHead;
        cur = cur->next->next;
        while (cur) {
            oddTail->next = cur;
            oddTail = oddTail->next;
            cur = cur->next;
            if (cur) {
                evenTail->next = cur;
                evenTail = evenTail->next;
                // 这里要记得再跳一下next，因为这个点已经处理过了
                cur = cur->next;
            }
            // 这里之所以不用把odd和even的next都置为nullptr，是因为原来的写法一次只操作奇数或者
            // 偶数当中的一个，奇数轮需要把偶数置空，反之同理
            // 现在每次都会操作两个，就不需要了
        }
        evenTail->next = nullptr;
        oddTail->next = evenHead;
        return oddHead;
    }
};

const int N = 105;

int n, m;	// n行m列

bool g[N][N];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int dis[N][N];

int bfs(int sx, int sy) {
	std::queue<std::pair<int, int>> q;
	q.push({sx, sy});
	dis[sx][sy] = 0;
	while(q.size()) {
		auto now_head = q.front();
		q.pop();
		int nx = now_head.first, ny = now_head.second;
		if(nx == n && ny == m) {
			return dis[nx][ny];
		}
		for(int i = 0;i < 4; i++) {
			int fx = nx + dx[i], fy = ny + dy[i];
			if(fx < 1 || fx > n || fy < 1 || fy > m) 
				continue;
			if(~dis[fx][fy] || g[fx][fy]) {
				continue;
			}
			dis[fx][fy] = dis[nx][ny] + 1;
			q.push({fx, fy});
		}
	}
}

int main() {
	std::string s;
	std::cin >> s;
	std::cout << "This is Hello World";
	return 0;
	memset(dis, -1, sizeof(dis));
    std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cin >> n >> m;
	for(int i = 1; i <=n ;i ++) {
		for(int j = 1; j <= m; j++) {
			std::cin >> g[i][j];
		}
	}
	std::cout << bfs(1, 1) << "\n";
}