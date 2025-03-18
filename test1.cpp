#include <iostream>
#include <vector>

using namespace std;
int check(vector<int> a, int x, int k, int larger) {
    if (a[x] >= k && larger) return 1;
    if (a[x] <= k && !larger) return 1;
    return 0;
}
vector<int> solve(vector<int> a, int k, int n) {
    vector<int> ans;
    int l = 0, r = n - 1;
    int mid = (l + r) / 2;
    int a1 = -1, a2 = -1;
    while (l <= r) {
        // 找第一个
        mid = (l + r) / 2;
        int flag = check(a, mid, k, 1);
        if (flag == 1) {
            a1 = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    if (a[a1] != k) {
        ans.push_back(-1);
        ans.push_back(-1);
        return ans;
    }
    ans.push_back(a1);
    l = 0, r = n - 1;
    while (l <= r) {
        // 找最后一个
        mid = (l + r) / 2;
        int flag = check(a, mid, k, 0);
        if (flag == 1) {
            a2 = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    ans.push_back(a2);
    return ans;
}
int main() {
    int n, q;
    cin >> n >> q;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int tmp;
        scanf("%d", &tmp);
        a.push_back(tmp);
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        vector<int> ans = solve(a, k, n);
        printf("%d %d\n", ans[0], ans[1]);
    }
}