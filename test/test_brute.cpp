#include "Pizza.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        pizza.fill(0, 0);
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
    }
    return 0;
}
