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
    void printShapes();
    bool fill(int r, int c);
    int getArea();
    void writeFilling(const char*);
private:
    std::vector<std::vector<IngreNum>> accum_tab;
    std::vector<std::vector<bool>> used;
    std::vector<std::vector<int>> ans;
    std::vector<std::vector<int>> shapes;
    int nrows, ncols, min_ing, max_ncells, area;
    void constructShapes();
    bool isAvailable(int row, int col, std::vector<int>& shape);
    void markUsed(int row, int col, std::vector<int>& shape);
};

#endif
