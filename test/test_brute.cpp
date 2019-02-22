#include "Pizza.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        for (int i = 0; i < 1000; i += 1) {
            for (int j = 0; j < 1000; j += 1) {
                pizza.fillS(i, j);
            }
        }
        for (int i = 0; i < 1000; i += 1) {
            for (int j = 0; j < 1000; j += 1) {
                pizza.fillB(i, j);
            }
        }
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
        if (argc > 2)
            pizza.outputAnswer(argv[2]);
        std::cout << "Output bmp file to pizzamap.bmp" << std::endl;
        pizza.writeFilling("pizzamap.bmp");
    }
    return 0;
}
