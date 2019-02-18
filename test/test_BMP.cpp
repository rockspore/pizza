#include "../include/BMP.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    vector<vector<vector<int>>> data(128, vector<vector<int>>(256, vector<int>(3, 0)));
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[0].size(); j++) {
            data[i][j][0] = i * 256 / data[0].size();
        }
    }

    BMPWrite("gradient.bmp", data);
}
