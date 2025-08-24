#include <iostream>
#include <string>

int n;

int main() {
    std::cin >> n;
    int cur = 0, num = 0;
    std::string s;
    while (true) {
        s = std::to_string(num);
        if (cur + s.length() >= n) {
            std::cout << s[n - cur - 1];
            break;
        }
        else {
            cur += s.length();
            num += 2;
        }
    }
    return 0;
}