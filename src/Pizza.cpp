/*************************************
 * 2019 Google HashCode Challenge    *
 * Practice Problem: Pizza           *
 * Team HUGE                         *
 * Yiran Hu and Luwei Ge             *
 * Feb, 2019                         *
 *************************************/

#include <fstream>
#include <iostream>
#include "Pizza.h"

// class to store the accumulative number of tomatos and mushroom
IngreNum::IngreNum(int t, int m) {
    toma = t;
    mush = m;
}

// do a minus operation and return the smaller number of two ingredients
int IngreNum::operator - (IngreNum &in) {
    int t = toma - in.toma, m = mush - in.mush;
    return t < m ? t : m;
}

// construct Pizza object from the input file
Pizza::Pizza(char* filename) {
    std::fstream fs;
    fs.open(filename);
    if (fs.is_open()) {
        fs >> nrows >> ncols >> min_ing >> max_ncells;
        std::cout << "Number of rows is " << nrows << std::endl;
        std::cout << "Number of columns is " << ncols << std::endl;
        std::cout << "Minimum number of each ingredient cells in a slice is " << min_ing << std::endl;
        std::cout << "maximum total number of cells of a slice " << max_ncells << std::endl;
        std::string row;
        getline(fs, row);
        // construct the accumulative table
        accum_tab = std::vector<std::vector<IngreNum>>(nrows + 1, std::vector<IngreNum>(ncols + 1, IngreNum(0, 0)));
        for (int i = 1; i <= nrows; i++) {
            getline(fs, row);
            for (int j = 1; j <= ncols; j++) {
                accum_tab[i][j].toma = accum_tab[i][j - 1].toma
                                     + accum_tab[i - 1][j].toma
                                     - accum_tab[i - 1][j - 1].toma;
                accum_tab[i][j].mush = accum_tab[i][j - 1].mush
                                     + accum_tab[i - 1][j].mush
                                     - accum_tab[i - 1][j - 1].mush;
                if (row[j - 1] == 'T') {
                    accum_tab[i][j].toma += 1;
                } else {
                    accum_tab[i][j].mush += 1;
                }
            }
        }
        //printTable(true);
        fs.close();
    } else {
        std::cout << "Error opening input file!\n";
    }
}

// print out the table (for debug purpose)
void Pizza::printTable(bool f) {
    for (auto &row: accum_tab) {
        for (auto &e: row) {
            std::cout << (f ? e.mush : e.toma) << " ";
        }
        std::cout << std::endl;
    }
}
