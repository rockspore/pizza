#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    fstream fs;
    if (argc > 0)
        fs.open(argv[0]);
    else
        fs.open("../data/a_example.in");

    int n, m, min_ing, max_cell;
    vector<vector<int>> acct(n+1, vector<int>(m+1, 0));
    vector<vector<int>> accm(n+1, vector<int>(m+1, 0));

    if (fs.is_open()) {
        fs >> n >> m >> min_ing >> max_cell;
        std::string temp_str;
        getline(fs, temp_str);
        for (int i = 1; i <= n; i++) {
            getline(fs, temp_str);
            for (int j = 1; i <= m; j++) {
                acct[i][j] = acct[i-1][j] + acct[i][j-1] - acct[i-1][j-1];
                accm[i][j] = accm[i-1][j] + accm[i][j-1] - accm[i-1][j-1];
                if (temp_str[j-1] == 'T') {
                    acct[i][j] ++;
                } else {
                    accm[i][j] ++;
                }
            }
        }
        fs.close();
        
        // find rectangle shapes
        vector<vector<int>> shapes;
        for (int l = 1; l <= max_cell; l++) {
            for (int w = 1; w <= max_cell/l; w++) {
                if (l*w >= min_ing*2 && l*w <= max_cell) {
                    shapes.push_back(vector<int>(2, 0));
                    shapes[shapes.size()-1][0] = w;
                    shapes[shapes.size()-1][1] = l;
                }
            }
        }

        vector<vector<int>> rects;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < shapes.size(); k++) {
                    int i2 = i + shapes[k][0], j2 = j + shapes[k][1];
                    if (acct[i2][j2] + acct[i][j] - acct[i2][j] - acct[i][j2] >= min_ing && 
                        accm[i2][j2] + accm[i][j] - accm[i2][j] - accm[i][j2] >= min_ing) {
                        vector<int> temp_rect(4, 0);
                        temp_rect[0] = i;
                        temp_rect[1] = j;
                        temp_rect[2] = i2-1;
                        temp_rect[3] = j2-1;
                        rects.push_back(temp_rect);
                    }
                }
            }
        }


    } else {
        cout << "Error opening the file\n";
    }

    return 0;
}
