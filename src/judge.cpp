/*************************************
 * 2019 Google HashCode Challenge    *
 * Practice Problem: Pizza           *
 * Team HUGE                         *
 * Yiran Hu and Luwei Ge             *
 * Feb, 2019                         *
 *************************************/

#include <iostream>
#include <fstream>
#include "Pizza.h"

using namespace std;

int Pizza::pizzaJudge() {
    bool f = true;
    int area = 0;
    for (int i = 0; i < ans.size() && f; i++) {
        for (int j = i + 1; j < ans.size(); j++) {
            if (overlap(ans[i], ans[j])) {
                f = false;
                break;
            }
            area += (ans[i][1] - ans[i][0]) * (a[i][3] - a[i][2]);
        }
    }

    if (f) {
        return area;
    } else {
        return -1;
    }
}

bool overlap(vector<int>& a, vector<int>& b) {
    return overlap1d(a[0], a[1], b[0], b[1]) && overlap1d(a[2], a[3], b[2], b[3]);
}

bool overlap1d(int a, int b, int c, int d) {
    return !((a<c && a<d && b<c && b<d) || (a>c && a>d && b>c && b>d));
}
