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
#include "BMP.h"
#include <algorithm>

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
    fs.open(filename, std::fstream::in);
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
        used = std::vector<std::vector<bool>>(nrows, std::vector<bool>(ncols, false));
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
        constructShapes();
        area = 0;
    } else {
        std::cout << "Error opening input file!\n";
    }
}

void Pizza::constructShapes() {
    for (int l = 1; l <= max_ncells; l++) {
        for (int w = 1; w <= max_ncells/l; w++) {
            if (l*w >= min_ing*2 && l*w <= max_ncells) {
                shapes.push_back(std::vector<int>(2, 0));
                shapes[shapes.size()-1][0] = w;
                shapes[shapes.size()-1][1] = l;
                // cout << "Adding shape: " << w << " * " << l << endl;
            }
        }
    }
    std::sort(shapes.begin(), shapes.end(), [] (std::vector<int> &v1, std::vector<int> &v2)
        { return v1[0]*v1[1] > v2[0]*v2[1]; });
}

bool Pizza::fill(int r, int c) {
    if (r < 0 || r > nrows - 1) {
        return false;
    }
    if (c < 0 || c > ncols - 1) {
        return false;
    }
    for (auto& s: shapes) {
        //std::cout << s[0] << "x" << s[1] << "\n";
        if (isAvailable(r, c, s)) {
            //std::cout << "find available area to fill\n";
            markUsed(r, c, s);
            ans.push_back(std::vector<int>({r, c, r + s[0] - 1, c + s[1] - 1}));
            fill(r + s[0], c);
            fill(r, c + s[1]);
            return true;
        }
    }
    //if (!fill(r + 1, c))
    //    fill(r, c + 1);
    return false;
}

void Pizza::outputAnswer(const char* filename) {
    fstream fs;
    fs.open(filename, std::fstream::out);
    fs << ans.size() << std::endl;
    for (auto &a: ans) {
        fs << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << std::endl;
    }
}

bool Pizza::isAvailable(int row, int col, std::vector<int>& shape) {
    if (row + shape[0] > nrows || col + shape[1] > ncols)
        return false;
    for (int r = row; r < row + shape[0]; r++) {
        for (int c = col; c < col + shape[1]; c++) {
            if (used[r][c]) return false;
        }
    }
    int r1 = row, r2 = row + shape[0] - 1;
    int c1 = col, c2 = col + shape[1] - 1;
    int num_toma = accum_tab[r1][c1].toma + accum_tab[r2+1][c2+1].toma
                 - accum_tab[r1][c2+1].toma - accum_tab[r2+1][c1].toma;
    int num_mush = accum_tab[r1][c1].mush + accum_tab[r2+1][c2+1].mush
                 - accum_tab[r1][c2+1].mush - accum_tab[r2+1][c1].mush;
    return (num_toma >= min_ing) && (num_mush >= min_ing);
}

void Pizza::markUsed(int row, int col, std::vector<int>& shape) {
    for (int r = row; r < row + shape[0]; r++) {
        for (int c = col; c < col + shape[1]; c++) {
            used[r][c] = true;
        }
    }
    area += shape[0]*shape[1];
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

// print out the shapes (for debug purpose)
void Pizza::printShapes() {
    for (auto &s: shapes) {
        std::cout << "WxL: " << s[0] << "x" << s[1] << "\n";
    }
}

int Pizza::getArea() {
    return area;
}

void Pizza::writeFilling(const char* filename) {
    std::vector<std::vector<std::vector<int>>> data(used.size(), std::vector<std::vector<int>>(used[0].size(), std::vector<int>(3, 0)));
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) {
            if (used[i][j]) {
                data[i][j][0] = 255;
                data[i][j][1] = 255;
                data[i][j][2] = 255;
            }
        }
    }
    BMPWrite(filename, data);
}
