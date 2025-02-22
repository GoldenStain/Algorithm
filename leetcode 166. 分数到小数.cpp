class Solution {
    typedef long long LL;
public:
    string fractionToDecimal(int numerator, int denominator) {
        LL N = numerator, D = denominator;
        std::string q1 = "", q2 = "";
        if (N*D < 0) {
            q1 = "-";
        }
        N = std::abs(N);
        D = std::abs(D);
        std::unordered_map<LL, int> M;
        LL q = N/D, r = N%D;
        q1 += std::to_string(q);
        if (!r)
            return q1;
        M[r] = 0;
        r *= 10;
        int j = -1;
        for(int i = 1;;i++) {
            q = r/D;
            r = r%D;
            q2.append(1, q + '0');
            // 结束
            if (!r || M.count(r)) {
                if (M.count(r))
                    j = M[r];
                break;
            }
            M[r] = i;
            r*=10;
        }
        if (!r) {
            return q1 + "." + q2;
        }
        q2.insert(j, "(");
        q2 += ")";
        return q1 + "." + q2;
    }
};