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
    string a;
    vector<int> A;
    string b;
    vector<int> B;

    cin >> a >> b;

    for (int i = a.size() - 1; i >= 0; i--) A.push_back(a[i] - '0');
    for (int i = b.size() - 1; i >= 0; i--) B.push_back(b[i] - '0');

    vector<int> C = div(A, B);

    for (int i = C.size() - 1; i >= 0; i--) cout << C[i];

    cout << endl;

    while (A.size() > 1 && A.back() == 0) A.pop_back();
    for (int i = A.size() - 1; i >= 0; i--) cout << A[i];

    return 0;
}