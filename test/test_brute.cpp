#include "Pizza.h"
#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        int ntrials = 200, area = 0;
        int ncols = pizza.getNumCols(), nrows = pizza.getNumRows();
        if (argc > 3)
            ntrials = atoi(argv[3]);
        while (ntrials > 0) {
            pizza.reset();
            for (int i = 0; i < nrows; i += 1) {
                for (int j = 0; j < ncols; j += 1) {
                pizza.fill(i, j);
                }
            }
            std::cout << "Filled Area: " << pizza.getArea() << "\n";
            if (area < pizza.getArea()) {
                area = pizza.getArea();
                if (argc > 2)
                    pizza.outputAnswer(argv[2]);
            }
            if (area == ncols * nrows)
                break;
            ntrials--;
        }
        std::cout << "Maximized Filled Area: " << area << "\n";

        std::cout << "Output bmp file to pizzamap.bmp" << std::endl;
        pizza.writeFilling("pizzamap.bmp");
    }
    return 0;
}
