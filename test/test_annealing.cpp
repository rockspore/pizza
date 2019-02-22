#include "Pizza.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        int nrows = pizza.getNumRows(), ncols = pizza.getNumCols();
        for (int i = 0; i < nrows; i += 1) {
            for (int j = 0; j < ncols; j += 1) {
                pizza.fillSV(i, j);
                pizza.fillSH(i, j);
                pizza.fillB(i, j);
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
        double prob;
        int tot_time = 1; // Minutes
        if (argc > 6) prob = std::stod(argv[6]);
        else          prob = 0.5;
        if (argc > 7) tot_time = std::stoi(argv[7])*60000;
        else          tot_time = 60000;


        int count = 0;
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int duration = 0; duration <= tot_time;) {
            for (int i = 0; i <= nrows-block_size; i += stride_size) {
                for (int j = 0; j <= ncols-block_size; j += stride_size) {
                    int r1 = i, c1 = j,
                        r2 = i+block_size-1,
                        c2 = j+block_size-1;
                    // std::cout << "Annealing area [" << r1 << ", " << c1 << "] -> [" << r2 << ", " << c2 << "]\n";
                    auto t2 = std::chrono::high_resolution_clock::now();
                    duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
                    if (count % 1000 == 0) {
                        std::cout << duration / 60000.0 << " ";
                    }
                    pizza.anneal(r1, c1, r2, c2, prob, count % 1000 == 0);
                    count++;
                    if (duration > tot_time) break;
                }
                if (duration > tot_time) break;
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
