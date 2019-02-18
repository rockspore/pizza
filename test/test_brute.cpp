#include "Pizza.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        pizza.fill(0, 0);
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
        std::cout << "Output bmp file to pizzamap.bmp" << std::endl;
        pizza.writeFilling("pizzamap.bmp");
    }
    return 0;
}
