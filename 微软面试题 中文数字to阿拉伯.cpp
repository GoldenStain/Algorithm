#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <io.h>      // Windows 宽字符支持
#include <fcntl.h>   // 控制台模式设置

static const std::wstring digit = L"零一二三四五六七八九";
static const std::wstring unit = L"十廿卅百千万亿";
static const std::vector<long long> units = {10, 20, 30, 100, 1000, 10000, 100000000};

// 中文字符转数值（0-9）
long long value_for_digit(wchar_t c) {
    size_t pos = digit.find(c);
    return (pos != std::wstring::npos) ? static_cast<long long>(pos) : -1;
}

// 递归解析中文数字
long long parse_chinese_number(const std::wstring& s, int l, int r) {
    if (l > r) return 0;
    long long ans = 0;
    int pos_of_greatest_unit = -1; long long value_of_greatest_unit = -1;

    // 找最大的单位，拆成两半
    for (int i = l; i <= r; i++) {
        size_t pos = unit.find(s[i]);
        if (pos == std::wstring::npos)
            continue;
        pos = static_cast<int>(pos);
        long long value_of_pos = units[pos];
        if (value_of_pos > value_of_greatest_unit) {
            pos_of_greatest_unit = i;
            value_of_greatest_unit = value_of_pos;
        }
    }
    // 不存在单位
    if (pos_of_greatest_unit == -1) {
        for (int i = l; i <= r; i++)
            ans = ans * 10 + value_for_digit(s[i]);
        return ans;
    }

    // 有单位
    long long left = parse_chinese_number(s, l, pos_of_greatest_unit - 1), right = parse_chinese_number(s, pos_of_greatest_unit + 1, r);
    // 为什么需要这个特判？ 样例：八亿四千八百卅万零二千六百廿五
    if (!left)
        left = 1;
    return left * value_of_greatest_unit + right;
}

long long convert_chinese_number(const std::wstring& s) {
    return parse_chinese_number(s, 0, s.size() - 1);
}

// 单调栈
long long convert_stack(std::wstring& s) {
    std::stack<long long > stk;
    int n =s.size();
    for(int i = 0; i < n; i++) {
        size_t pos = unit.find(s[i]);
        // 普通数字  直接入栈
        if (pos == std::wstring::npos) {
            stk.push(value_for_digit(s[i]));
        }
        // 是一个单位  比如： 两亿三千五百万
        // 我们现在到了“万”
        // 那么  在亿和万之间的部分都要乘以万
        // 也就是我们要在 i 和 i左边第一个比i大的数字之间
        // 都乘以一个i
        else {
            pos = static_cast<int>(pos);
            long long unit_value = units[pos], sum_of_smaller = 0;
            while (stk.size() && stk.top() < unit_value) {
                sum_of_smaller += stk.top();
                stk.pop();
            }
            // 如果一个都没加，要乘以1而不是0
            stk.push(sum_of_smaller ? unit_value * sum_of_smaller : unit_value);
        }
    }
    long long ans = 0;
    while(stk.size()) {
        ans += stk.top();
        stk.pop();
    }
    return ans;
}

int main() {
    // 样例：八亿四千八百卅万零二千六百廿五
    // Windows 控制台宽字符支持
    _setmode(_fileno(stdin), _O_WTEXT);
    _setmode(_fileno(stdout), _O_WTEXT);

    std::wstring s;
    std::wcin >> s;
    // 递归
    long long ans = convert_chinese_number(s);
    std::wcout << ans << std::endl;

    // 单调栈
    ans = convert_stack(s);
    std::wcout << ans << std::endl;
    return 0;
}
