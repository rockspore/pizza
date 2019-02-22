#include "Pizza.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pizza(argv[1]);
        pizza.printShapes();
        for (int i = 0; i < 1000; i += 1) {
            for (int j = 0; j < 1000; j += 1) {
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
        if (argc > 7) tot_time = std::stoi(argv[7]);
        else          tot_time = 1;
        

        int count = 0;
        for (int tstart = clock(), telps = 0; 1.0 * (telps) / CLOCKS_PER_SEC / 60 <= tot_time;) {
            for (int i = 0; i <= 1000-block_size; i += stride_size) {
                for (int j = 0; j <= 1000-block_size; j += stride_size) {
                    int r1 = i, c1 = j,
                        r2 = i+block_size-1,
                        c2 = j+block_size-1;
                    // std::cout << "Annealing area [" << r1 << ", " << c1 << "] -> [" << r2 << ", " << c2 << "]\n";
                    telps = clock()-tstart;
                    if (count % 1000 == 0) {
                        std::cout << 1.0 * (telps) / CLOCKS_PER_SEC / 60.0 << " ";
                    }
                    pizza.anneal(r1, c1, r2, c2, prob, count % 1000 == 0);
                    count++;
                }
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
