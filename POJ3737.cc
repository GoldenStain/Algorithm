#include <stdio.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>

#define For(i, j, n) for (int i = j; i <= n; ++i)

const double pi = acos(-1.0);
const double eps = 1e-9;

double S;  // 表面积

double r, h;  //	半径和高
double l;	//	母线长

double GetVolume(const double &r) {
    l = (S - r * r) / r;
    h = sqrt(l * l - r * r);
    return pi * r * r * h / 3.0;
}

inline double TernarySearch() {
    double leftBound = 0.0, rightBound = sqrt(S/2);
	double V1, V2, m1, m2;
    while (rightBound - leftBound > eps) {
        double gap = (rightBound - leftBound) / 3.0;
        m1 = leftBound + gap, m2 = rightBound - gap;
        V1 = GetVolume(m1), V2 = GetVolume(m2);
        if (V1 > V2) {
            rightBound = m2;
        } else {
            leftBound = m1;
        }
    }
    r = rightBound;
	return GetVolume(r);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout << std::fixed << std::setprecision(2);
    while (std::cin >> S) {
		S /= pi;
        double ans = TernarySearch();
        std::cout << ans << std::endl << h << std::endl << r << std::endl;
    }
    return 0;
}
