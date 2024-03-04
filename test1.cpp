#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#define For(i, j, n) for(int i = j ; i <= n ; ++i)
using namespace std;

void mystrcpy(char *dest, char *src, int len)
{
  strncpy(dest, src, len);
  
}

int main()
{
    char dest[32] = "", src[32] = "abcdefg";
    mystrcpy(dest, src, 2);
    for(int i = 0; i <= 2; i++)
        if(dest[i] == '\0')
            cout << 'y' << endl;
    cout << strlen(dest) << endl << dest << endl;
    return 0;
}
