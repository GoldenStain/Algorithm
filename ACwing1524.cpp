#include <iostream>
#include <cstdio>
#include <cstdlib>

int main() {
	std::string input;
	std::getline(std::cin, input);
	int ans = 0, j;
	for(int i = 0; i < input.size(); i++) {
		// 统计奇数长度
		int l = i - 1, r = i + 1;
		while(l >= 0 && r < input.size() && input[l] == input[r]) 
			l--, r++;
		ans = std::max(ans, r - l - 1);
		// 统计偶数长度
		l = i; r = i + 1;
		while(l >= 0 && r < input.size() && input[l] == input[r]) 
			l--, r++;
		ans = std::max(ans, r - l - 1);
	}
	std::cout << ans << std::endl;
}