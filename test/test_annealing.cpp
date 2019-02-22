#include "Pizza.h"
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        for (int i = 0; i < 1000; i += 1) {
            for (int j = 0; j < 1000; j += 1) {
            pizza.fill(i, j);
            }
        }
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
        if (argc > 2)
            pizza.outputAnswer(argv[2]);
        std::cout << "Output bmp file to pizzamap.bmp" << std::endl;
        pizza.writeFilling("pizzamap.bmp");

        // Annealing
        int block_size = std::stoi(argv[4]);
        int stride_size = std::stoi(argv[5]);
        for (int i = 0; i < 1000; i += stride_size) {
            for (int j = 0; j < 1000; i += stride_size) {
                int r1 = i, c1 = j,
                    r2 = std::min(i+block_size-1, 1000),
                    c2 = std::min(j+block_size-1, 1000);
                pizza.anneal(r1, c1, r2, c2, 0.9);
            }
        }
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
        if (argc > 3)
            pizza.outputAnswer(argv[3]);
        std::cout << "Output bmp file to pizzamap_anneal.bmp" << std::endl;
        pizza.writeFilling("pizzamap_anneal.bmp");
        
    }
    return 0;
}
