#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int d = 3;

bool cmp(vector<int> &A, vector<int> &B, int l, int len) {
    if (l + len < A.size() && A[l + len]) return true;
    for (int i = len - 1; i >= 0; i--) {
        if (A[l + i] != B[i]) return A[l + i] > B[i];
    }
    return true;
}

vector<int> div(vector<int> &A, vector<int> &B) {
    vector<int> ans;
    int n = A.size(), m = B.size();
    for (int i = n - m; i >= 0; i--) {
        int cnt = 0;
        while (cmp(A, B, i, m)) {
            // 减去
            cnt++;
            for (int j = 0; j < m; j++) {
                if (A[i + j] < B[j]) A[i + j + 1]--, A[i + j] += 10;
                A[i + j] -= B[j];
            }
        }
        ans.push_back(cnt);
    }
    reverse(ans.begin(), ans.end());
    while (ans.size() > 1 && ans.back() == 0) ans.pop_back();
    if (ans.empty()) ans.push_back(0);
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::string a, b;
    std::cin >> a >> b;
    int sa = a.size(), sb = b.size();
    std::vector<std::vector<int>> f(sa, std::vector<int>(sb, 0));
    int ans = 0;
    for(int i = 0; i < sa; i++)
        f[i][0] = b[0] == a[i], ans = std::max(ans, f[i][0]);
    for(int i = 0; i < sb; i++)
        f[0][i] = a[0] == b[i], ans = std::max(ans, f[0][i]);
    for(int i = 1; i < sa; i++)
        for(int j = 1; j < sb; j++)
            f[i][j] = (a[i] == b[j])?f[i - 1][j - 1] + 1:0, ans = std::max(ans, f[i][j]);
    std::cout << ans << std::endl;
    return 0;
}