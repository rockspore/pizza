/*************************************
 * 2019 Google HashCode Challenge    *
 * Practice Problem: Pizza           *
 * Team HUGE                         *
 * Yiran Hu and Luwei Ge             *
 * Feb, 2019                         *
 *************************************/

#include <iostream>
#include <fstream>
#include "../include/Pizza.h"
#include <cstdlib>

using namespace std;

bool overlap1d(int a, int b, int c, int d) {
    return !((a<c && a<d && b<c && b<d) || (a>c && a>d && b>c && b>d));
}

bool overlap(vector<int>& a, vector<int>& b) {
    return overlap1d(a[0], a[1], b[0], b[1]) && overlap1d(a[2], a[3], b[2], b[3]);
}

int Pizza::pizzaJudge() {
    bool f = true;
    int area = 0;
    for (int i = 0; i < ans.size() && f; i++) {

        int r1 = min(ans[i][0], ans[i][2]), r2 = max(ans[i][0], ans[i][2]),
            c1 = min(ans[i][1], ans[i][3]), c2 = max(ans[i][1], ans[i][3]),
            thisarea = (r2 - r1 + 1) * (c2 - c1 + 1),
            num_toma = accum_tab[r1][c1].toma + accum_tab[r2+1][c2+1].toma
                    - accum_tab[r1][c2+1].toma - accum_tab[r2+1][c1].toma,
            num_mush = accum_tab[r1][c1].mush + accum_tab[r2+1][c2+1].mush
                    - accum_tab[r1][c2+1].mush - accum_tab[r2+1][c1].mush,
            num_ing = min(num_toma, num_mush);

        if (thisarea > max_ncells || num_ing < min_ing) {
            f = false;
            break;
        }

        for (int j = i + 1; j < ans.size(); j++) {
            if (overlap(ans[i], ans[j])) {
                f = false;
                break;
            }
        }

        area += thisarea;
    }

    if (f) {
        return area;
    } else {
        return -1;
    }
}

