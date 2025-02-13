#include <iostream>
#include <vector>

// solution 1

std::vector<int> add(std::vector<int> &A, std::vector<int> &B) {
    int i = 0, carry = 0;
    while (i < A.size()) {
        if (i < B.size()) {
            A[i] = A[i] + B[i] + carry;
            carry = A[i] / 10;
            A[i] %= 10;
        }
        else {
            A[i] += carry;
            carry = A[i] / 10;
            A[i] %= 10;
        }
        i++;
    }
    if (carry)
        A.emplace_back(carry);
    return A;
}

int main() {
    std::string a, b;
    std::vector<int> A, B;
    std::cin >> a >> b;
    for(int i = a.size() - 1; i >=0; i--)
        A.emplace_back(a[i] - '0');
    for(int i = b.size() - 1; i >= 0; i--)
        B.emplace_back(b[i] - '0');
    if (A.size() >= B.size())
        A = add(A, B);
    else
        A = add(B, A);
    for(int i = A.size() - 1; i >= 0; i--)
        printf("%c", A[i] + '0');
    return 0;
}

// super solution
#include <iostream>
#include <vector>

constexpr int Base = 1000000000, Cnt = 9;

std::vector<int> add(std::vector<int> &A, std::vector<int> &B) {
    int i = 0, carry = 0;
    while (i < A.size()) {
        if (i < B.size()) {
            A[i] = A[i] + B[i] + carry;
            carry = A[i] / Base;
            A[i] %= Base;
        } else {
            A[i] += carry;
            carry = A[i] / Base;
            A[i] %= Base;
        }
        i++;
    }
    if (carry) A.emplace_back(carry);
    return A;
}

int main() {
    std::string a, b;
    std::vector<int> A, B;
    std::cin >> a >> b;
    for (int i = a.size() - 1, j = 0, t = 1, sum = 0; i >= 0; i--) {
        sum = sum + (a[i] - '0') * t;
        j++;t*=10;
        if (j == Cnt || i == 0) {
            A.push_back(sum);
            j = 0;
            sum = 0;
            t = 1;
        }
    }
    for (int i = b.size() - 1, j = 0, t = 1, sum = 0; i >= 0; i--) {
        sum = sum + (b[i] - '0') * t;
        j++;t*=10;
        if (j == Cnt || i == 0) {
            B.push_back(sum);
            j = 0;
            sum = 0;
            t = 1;
        }
    }
    if (A.size() >= B.size())
        A = add(A, B);
    else
        A = add(B, A);
    while(A.back() == 0)
        A.pop_back();
    printf("%d", A[A.size() - 1]);
    for(int i = A.size() - 2; i>=0; i--)
        printf("%09d", A[i]);
    return 0;
}