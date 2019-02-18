#include "Pizza.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 2) {
        Pizza pizza(argv[1]);
        pizza.fill(0, 0);
        pizza.writeFilling(argv[2]);
    }
    return 0;
}
