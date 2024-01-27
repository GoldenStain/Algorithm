#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <set>
#define For(i, j, n) for (int i = j; i <= n; ++i)
using namespace std;

string date;
set <string> S;
string y[3];
int days[2][14] = {{0, 31, 28, 31, 20, 31, 30, 31, 31, 30, 31, 30, 31},
                  {0, 31, 29, 31, 20, 31, 30, 31, 31, 30, 31, 30, 31}};

string is_year(int k, int w)
{
    string q = (w == 0) ? "19" : "20";
    string res;
    if (k == 0)
        res = q + y[0] + "-" + y[1] + "-" + y[2];
    else if (k == 1)
        res = q + y[2] + "-" + y[0] + "-" + y[1];
    else
        res = q + y[2] + "-" + y[1] + "-" + y[0];
    //cout << res << endl;
    return res;
}

bool check(string t)
{
    string yy = t.substr(0, 4);
    //cout << yy << " ";
    int tmp = atoi(yy.c_str()), this_year = tmp;
    if (tmp < 1960 || tmp > 2059)
    {
        //cout << "wrong year" << endl;
        return false;
    }
    yy = t.substr(5, 2);
    tmp = atoi(yy.c_str());
    int this_month = tmp;
    //cout << yy << " ";
    if (tmp < 1 || tmp > 12)
    {
        //cout << "wrong month" << endl;
        return false;
    }
    yy = t.substr(8, 2);
    tmp = atoi(yy.c_str()); // ÈÕÆÚ
    int this_day = tmp;
    //cout << yy << endl;
    //cout << "it is " << this_year << " " << this_month << " " << this_day << endl;
    int pos = (this_year % 400 == 0) || (this_year % 4 == 0 && this_year % 100 != 0);
    //cout << "pos " << pos << " " << "limit " << days[pos][this_month] << endl;
    if (this_day <= 0 || this_day > days[pos][this_month])
    {
        //cout << "wrong day" << endl;
        return false;
    }
    return true;
}

int main()
{
    cin >> date;
    y[0] = {date[0], date[1]};
    y[1] = {date[3], date[4]};
    y[2] = {date[6], date[7]};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
        {
            //cout << i << ' ' << j << endl;
            string res = is_year(i, j);
            if (check(res) && !S.count(res))
            {
                S.insert(res);
            }
        }
    for(string tmp : S)
        cout << tmp << endl;
    return 0;
}
