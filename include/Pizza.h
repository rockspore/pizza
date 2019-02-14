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
    void printTable(bool f = true);
private:
    std::vector<std::vector<IngreNum>> accum_tab;
    std::vector<std::vector<int>> ans;
    int nrows, ncols, min_ing, max_ncells;
};

#endif