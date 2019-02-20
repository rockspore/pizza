#include "Pizza.h"
#include <iostream>
#include <random>
#include <algorithm>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        std::vector<int> vrow, vcol;
        for (int i = 0; i < 1000; i++) {
            vrow.push_back(i);
            vcol.push_back(i);
        }
        std::random_device rd;
        auto rng = std::mt19937(rd());
        std::shuffle(vrow.begin(), vrow.end(), rng);
        std::shuffle(vcol.begin(), vcol.end(), rng);
        for (int i = 0; i < 1000; i += 1) {
            for (int j = 0; j < 1000; j += 1) {
            pizza.fill(999-i, j);
            }
        }
        std::cout << "Filled Area: " << pizza.getArea() << "\n";
        if (argc > 2)
            pizza.outputAnswer(argv[2]);
        //std::cout << "Output bmp file to pizzamap.bmp" << std::endl;
        //pizza.writeFilling("pizzamap.bmp");
    }
    return 0;
}
