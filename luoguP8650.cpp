#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

string str;
int step, len, cnt;
int get_len();
int get_primary();

int get_primary()
{
    
    //cout << "1 " << step << endl;
    if(str[step] == '(')
    {
        step++;
        int ans = get_len();
        //cout << "done " << step << endl;
        step++;
        return ans;
    }
    if(str[step] == 'x')
    {
        //cout << "x at" << step << endl;
        int k = step;
        while(str[k] == 'x')
            k++;
        int ans = k - step;
        step = k;
        //cout << "1 ends at" << step << endl;
        return ans;
    }
    return 0;
}

int get_len()
{
    
    //cout << "2 " << step << endl;
    int ans = 0;
    ans += get_primary();
    while(1)
    {
        if(str[step] == '|')
        {
            step++;
            ans = max(ans, get_len());
        }
        else if(str[step] == '(' || str[step] == 'x') 
            ans += get_primary();
        else
            break;
    }
    return ans;
}

int main()
{
    cin >> str;
    len = str.length();
    cout << get_len();
    return 0;
}
