#include <iostream>
#include <string>

constexpr int N = 1005;

std::string s;
int f[N][N];

int main() {
    std::cin >> s;
    for(int i = 0; i + 1 < s.length(); i++)
        f[i][i + 1] = s[i] == s[i + 1] ? 0 : 1;
    for(int len = 3; len <= s.length(); len++)
        for(int l = 0; l + len <= s.length(); l++) {
            int r = l + len - 1;
            f[l][r] = (s[l] == s[r]) ? f[l + 1][r - 1] : std::min(f[l + 1][r], f[l][r - 1]) + 1;
        }
    std::cout << f[0][s.length() - 1];
}