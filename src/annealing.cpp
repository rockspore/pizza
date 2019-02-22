/*************************************
 * 2019 Google HashCode Challenge    *
 * Practice Problem: Pizza           *
 * Team HUGE                         *
 * Yiran Hu and Luwei Ge             *
 * Feb, 2019                         *
 *************************************/

#include "Pizza.h"
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

// Randomly remove a certain amount of slices in an area and refill.
// If the newly found solution includes more cells then adopt the new solution
void Pizza::anneal(int r1, int c1, int r2, int c2, double prob, bool output) {
    srand ( unsigned ( time(0) ) );

    vector<int> del_slices; // Marks delected answers
    int old_area = area, old_ans_size = ans.size(); // Record old parameters.
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i][0] < r1 || ans[i][1] < c1 || ans[i][0] > r2 || ans[i][1] > c2) {continue;}
        if ((1.0 * rand() / RAND_MAX) <= prob) {
            del_slices.push_back(i);
            unmarkUsed(ans[i]);
        }
    }

    fillArea(max(r1-15, 0), max(c1-15, 0), min(r2+15, nrows-1), min(c2+15, ncols-1));
    
    if (area >= old_area) {
        // Accept new solution
        if (output)
            cout << area << endl;
        for (int i : del_slices) {
            ans[i][0] = -1;
        }
        vector<vector<int>> temp_ans;
        for (vector<int>& slice : ans) {
            if (slice[0] >= 0) {
                temp_ans.push_back(slice);
            }
        }
        ans.swap(temp_ans);
    } else {
        // Recover old solution
        for (int i = old_ans_size; i < ans.size(); i++) {
            unmarkUsed(ans[i]);
        }
        for (int i : del_slices) {
            markUsed(ans[i]);
        }
        ans.erase(ans.begin()+old_ans_size, ans.end());
        if (output)
            cout << area << endl;
    }
}

void Pizza::unmarkUsed(const vector<int>& slice) {
    for (int i = slice[0]; i <= slice[2]; i++) {
        for (int j = slice[1]; j <= slice[3]; j++) {
            used[i][j] = false;
        }
    }
    area -= (abs(slice[2]-slice[0])+1) * (abs(slice[3]-slice[1])+1);
}

// Overloading markUsed()
void Pizza::markUsed(const vector<int>& slice) {
    for (int i = slice[0]; i <= slice[2]; i++) {
        for (int j = slice[1]; j <= slice[3]; j++) {
            used[i][j] = true;
        }
    }
    area += (abs(slice[2]-slice[0])+1) * (abs(slice[3]-slice[1])+1); 
}

// Try filling up a certain area
void Pizza::fillArea(int r1, int c1, int r2, int c2) {
    for (int i = r2; i >= r1; i--) {
        for (int j = c1; j <=c2; j++) {
            fillSV(i, j);
            fillSH(i, j);
            fillB(i, j);
        }
    }
}

// Try filling up a certain area
void Pizza::fillAreaR(int r1, int c1, int r2, int c2) {
    srand ( unsigned ( time(0) ) );
    vector<vector<int>> lineup((abs(r2-r1)+1)*(abs(c2-c1)+1), vector<int>(2, 0));
    int idx = 0;
    for (int i = r1; i <= r2; i++) {
        for (int j = c1; j <=c2; j++) {
            lineup[idx][0] = i;
            lineup[idx][1] = j;
            idx++;
        }
    }
    random_shuffle(lineup.begin(), lineup.end());
    for (vector<int>& p : lineup) {
        fillR(p[0], p[1]);
    }
}

// Filling with randomized shape order
bool Pizza::fillR(int r, int c) {
    srand ( unsigned ( time(0) ) );
    random_shuffle(shapesR.begin(), shapesR.end());
    if (r < 0 || r > nrows - 1) {
        return false;
    }
    if (c < 0 || c > ncols - 1) {
        return false;
    }
    for (auto& s: shapesR) {
        //std::cout << s[0] << "x" << s[1] << "\n";
        if (isAvailable(r, c, s)) {
            //std::cout << "find available area to fill\n";
            markUsed(r, c, s);
            ans.push_back(vector<int>({r, c, r + s[0] - 1, c + s[1] - 1}));
            //fill(r + s[0], c);
            //fill(r, c + s[1]);
            return true;
        }
    }
    //if (!fill(r + 1, c))
    //    fill(r, c + 1);
    return false;
    
}
