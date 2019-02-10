#include <fstream>
#include <iostream>
#include <vector>

class Pizza {
public:
    Pizza(char* filename) {
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
            for (int i = 0; i < nrows; i++) {
                getline(fs, row);
                //std::cout << row << std::endl;
                cells.push_back(std::vector<bool>(ncols));
                for (int j = 0; j < ncols; j++) {
                    cells[i][j] = (row[j] == 'T' ? true : false);
                }
            }
            fs.close();
        } else {
            std::cout << "Error opening input file!\n";
        }
    }
private:
    std::vector<std::vector<bool>> cells;
    int nrows, ncols, min_ing, max_ncells;
};

int main(int argc, char* argv[]) {
    if (argc > 1) {
        Pizza pz(argv[1]);
    }
    return 0;
}
