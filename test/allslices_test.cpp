#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

void findSlices(const char* filename, vector<vector<int>>& slices) {
    fstream fs;
    fs.open(filename, ios_base::in);
    int n, m, min_ing, max_cell;
    
    cout << "Reading file: " << filename << endl;
    if (fs.is_open()) {
        fs >> n >> m >> min_ing >> max_cell;
        vector<vector<int>> acct(n+1, vector<int>(m+1, 0));
        vector<vector<int>> accm(n+1, vector<int>(m+1, 0));

        std::string temp_str;
        getline(fs, temp_str);
        for (int i = 1; i <= n; i++) {
            getline(fs, temp_str);
            for (int j = 1; j <= m; j++) {
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
       
        cout << "Pizza size:" << n << " * " << m << endl;
        cout << "Minimum ingredient: " << min_ing << endl;
        cout << "Maximum slice: " << max_cell << endl;

        // find rectangle shapes
        vector<vector<int>> shapes;
        for (int l = 1; l <= max_cell; l++) {
            for (int w = 1; w <= max_cell/l; w++) {
                if (l*w >= min_ing*2 && l*w <= max_cell) {
                    shapes.push_back(vector<int>(2, 0));
                    shapes[shapes.size()-1][0] = w;
                    shapes[shapes.size()-1][1] = l;
                    // cout << "Adding shape: " << w << " * " << l << endl;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int k = 0; k < shapes.size(); k++) {
                    int i2 = i + shapes[k][0], j2 = j + shapes[k][1];
                    if (i2 > n || j2 > m) continue;
                    // cout << "Slice [" << i << "," << j << "]->[" << i2-1 << "," << j2-1 << "]" << endl;
                    // cout << "Tomatos: " << acct[i2][j2] + acct[i][j] - acct[i2][j] - acct[i][j2] << endl;
                    // cout << "Mushrooms: " << accm[i2][j2] + accm[i][j] - accm[i2][j] - accm[i][j2] << endl;
                    // cout << "Thanks for participating" << endl;
                    if (acct[i2][j2] + acct[i][j] - acct[i2][j] - acct[i][j2] >= min_ing && 
                        accm[i2][j2] + accm[i][j] - accm[i2][j] - accm[i][j2] >= min_ing) {
                        vector<int> temp_slice(4, 0);
                        temp_slice[0] = i;
                        temp_slice[1] = j;
                        temp_slice[2] = i2-1;
                        temp_slice[3] = j2-1;
                        slices.push_back(temp_slice);
                    }
                }
            }
        }


    } else {
        cout << "Error opening the file\n";
    }

}

vector<string> readPizza(const char* filename) {
// return a vector of strings, each string represents a row in the pizza.
    fstream fs;
    fs.open(filename, ios_base::in);
    int n, m, min_ing, max_cell;
    
    cout << "Reading file: " << filename << endl;
    if (fs.is_open()) {
        fs >> n >> m >> min_ing >> max_cell;
        cout << "Pizza size:" << n << " * " << m << endl;
        cout << "Minimum ingredient: " << min_ing << endl;
        cout << "Maximum slice: " << max_cell << endl;
        
        vector<string> pizza(n);
        string temp_str;
        getline(fs, temp_str);
        
        for (int i = 0; i < n; i++) {
            getline(fs, pizza[i]);
        }
        return pizza;
    } else {
        return vector<string>(0);
    }
}

void outputSlice(const vector<string>& pizza, vector<int> slice) {
// Give me a slice, I can output it for you
    cout << "Slice: [" << slice[0] << ", " << slice[1] << "] -> [" << slice[2] << ", " << slice[3] << "]\n";
    for (int i = slice[0]; i <= slice[2]; i++) {
        cout << pizza[i].substr(slice[1], slice[3] - slice[1] + 1) << endl;
    }
}

int main(int argc, char* argv[]){
    char *filename = new char(100);
    if (argc > 1) strcpy(filename, argv[1]);
    else strcpy(filename, "../data/a_example.in");

    vector<vector<int>> slices;
    findSlices(argv[1], slices);
    cout << slices.size() << endl;

    vector<string> pizza = readPizza(filename);
    for (int i = 0; i < slices.size(); i++) {
        outputSlice(pizza, slices[i]);
    }

}
