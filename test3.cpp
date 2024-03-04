#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <string>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

int main()
{
    char str[] = "Hello 1 2 3";
    cout << str << endl;
    char *token = strtok(str, " ");
    cout << str << " " << token << endl;
    while(token != NULL)
    {
        token = strtok(NULL, " ");
        cout << str << " " << token << endl;
    }
    return 0;
}
