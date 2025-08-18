
#include <algorithm>
#include <iostream>
#include <cstdio>

constexpr int N = 505, LEN = 30;
constexpr int UPPER = (1 << LEN) - 1;
int arr[N], T;

int len_of_bits(int x) {
    int ans = 0;
    while (x) {
        ans++;
        x>>=1;
    }
    return ans?ans:1;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &T);
    int len;
    while (T--) {
        scanf("%d", &len);
        int _max = -1, sum = 0;
        for (int i = 1; i <= len; i++) {
            scanf("%d", &arr[i]);
            sum += arr[i];
            _max = std::max(_max, arr[i]);
        }
        int len = len_of_bits(_max);
        int upper = UPPER, mask = (1 << len) - 1;
        for (int i = 1; i <= len; i++) {
            upper &= arr[i];
        }
        upper &= mask;
        int x = mask ^ upper;
        sum += x;
        printf("%d %d\n", sum, x);
    }
    return 0;
}