#include <iostream>

int main() {
    int i = 2;
    do {
        std::cout << i << std::endl;
        i--;
    }while(i);

    i = 2;
    while(i) {
        std::cout << i << std::endl;
        i--;
    }
}