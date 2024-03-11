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

int main(int argc, char* argv[])
{
    char d[10], s[] = "abc";
    strncpy(d, s, 3);
    cout << strlen(d) << endl;
    return 0;
}
