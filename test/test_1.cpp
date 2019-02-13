#include "../src/Pizza.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        std::cout << "Mushroom table:\n";
        pizza.printTable(true);
        std::cout << "Tomato table:\n";
        pizza.printTable(false);
    }
    return 0;
}
