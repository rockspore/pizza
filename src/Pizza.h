/*************************************
 * 2019 Google HashCode Challenge    *
 * Practice Problem: Pizza           *
 * Team HUGE                         *
 * Yiran Hu and Luwei Ge             *
 * Feb, 2019                         *
 *************************************/

#ifndef PIZZA_H
#define PIZZA_H

#include <vector>

class Pizza {
public:
    Pizza(char* filename);
    int pizzaJudge();
private:
    std::vector<std::vector<bool>> cells;
    int nrows, ncols, min_ing, max_cells;
};

#endif
