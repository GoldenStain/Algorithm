#include <stdio.h>
#include <string.h>

#include <algorithm>
#include <cmath>
#include <iostream>
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
using namespace std;
class Solution {
   public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        int n = words.size(), len = 0;
        vector<string> ans;

        for (int i = 0; i < n; i++) {
            int j = i;
            len = words[i].size();
            for (j = i + 1; j < n; j++) {
                if (len + words[j].size() + 1 <= maxWidth)
                    len += words[j].size() + 1;
                else {
                    break;
                }
            }
            j--;
            int cnt = j - i, diff = maxWidth - len, quo = -1, r = -1;
            // cnt有可能是0，这一行只有一个单词
            if (cnt) {
                quo = diff / cnt;
                r = diff % cnt;
            }
            std::string tmp = words[i];

            for (int k = i + 1; k <= j; k++) {
                int cnt_empty = (j < n - 1) ? quo + 1 : 1;
                tmp.append(cnt_empty, ' ');
                if (j < n - 1 && r) {
                    tmp.append(1, ' ');
                    r--;
                }
                tmp += words[k];
            }

            if (quo == -1 || j == n - 1) tmp.append(maxWidth - len, ' ');

            ans.emplace_back(tmp);
            i = j;
        }
        return ans;
    }
};

int main() {
    std::vector<std::string> words = {"What",           "must",  "be",
                                      "acknowledgment", "shall", "be"};
    std::cout << "intpus: ";
    for (auto ai : words) {
        std::cout << ai << ",";
    }
    std::cout << std::endl;
    int maxWidth = 16;
    Solution solution;
    auto ans = solution.fullJustify(words, maxWidth);
    for (auto ai : ans) {
        std::cout << ai << ",";
    }
    return 0;
}