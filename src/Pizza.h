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

class IngreNum {
public:
    int toma, mush;
    IngreNum(int t, int m);
    int operator - (IngreNum &in);
};

class Pizza {
public:
    Pizza(char* filename);
    int pizzaJudge();
private:
    std::vector<std::vector<IngreNum>> accum_tab;
    int nrows, ncols, min_ing, max_ncells;
    void printTable(bool f = true);
    std::vector<std::vector<int>> ans;
};

#endif
