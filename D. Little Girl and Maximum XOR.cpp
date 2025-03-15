// wrong solution
int get_length(long long num) {
    double log_val = std::log2(static_cast<double>(num));
    int length = static_cast<int>(std::floor(log_val));
    return length;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    long long l, r;
    std::cin >> l >> r;
    if (l == r) {
        std::cout << "0\n";
        return 0;
    }
    long long diff = r - l;
    int l_diff = get_length(diff), l_r = get_length(r),l_l = get_length(l);
    long long res = (1<<(l_diff+1)) - 1;
    for (int i = std::max(l_diff, l_l) + 1; i <= l_r; i++) {
        res += r & (1 << i);
    }
    std::cout << res << std::endl;
    return 0;
}

// real solution
int get_length(long long num) {
    double log_val = std::log2(static_cast<double>(num));
    int length = static_cast<int>(std::floor(log_val));
    return length;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    long long l, r;
    std::cin >> l >> r;
    if (l == r) {
        std::cout << "0\n";
        return 0;
    }
    long long p = (1ll << 62);
    while(p&&(l&p)==(r&p))
        p>>=1;
    p = (p<<1)-1;
    std::cout << p << std::endl;
    return 0;
}
