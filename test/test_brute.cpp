#include "Pizza.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        for (int i = 0; i < 1000; i += 2) {
            pizza.fill(i, 0);
            pizza.fill(0, i);
            pizza.fill(i, i);
        }
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
        if (argc > 2)
            pizza.outputAnswer(argv[2]);
        std::cout << "Output bmp file to pizzamap.bmp" << std::endl;
        pizza.writeFilling("pizzamap.bmp");
    }
    return 0;
}
