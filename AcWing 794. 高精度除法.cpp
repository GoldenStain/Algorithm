#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int d = 3;

vector<int> div(vector<int> &A, int b, int &r)
{
    r = 0;
    vector<int> C;
    for(int i = A.size() - 1; i >= -d - 1; i--) {
        if (i >= 0)
            r = (r * 10) + A[i];
        else
            r = r * 10;
        C.push_back(r / b);
        r %= b;
    }
    if (d && C.size() >= 2 && C.back() >= 5)
        C[C.size() - 2] += 1, C.pop_back();
    // C: 高->低
    reverse(C.begin(), C.end());
    // 低->高
    while(C.size() > 1 && !C.back())
        C.pop_back();
    return C;
}

int main()
{
    string a;
    vector<int> A;

    int B;
    cin >> a >> B;
    for (int i = a.size() - 1; i >= 0; i -- ) A.push_back(a[i] - '0');

    int r;
    auto C = div(A, B, r);

    for (int i = C.size() - 1; i >= d; i -- ) cout << C[i];
    cout << ".";
    for (int i = d - 1; i >= 0; i--)
        cout << C[i];

    auto get_decimal = [](int x) {
        int res = 1;
        for(int i = 1;i <= x; i++)
            res *= 0.1;
        return x;
    };

    cout << endl << r * get_decimal(d) << endl;

    return 0;
}