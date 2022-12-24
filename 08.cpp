#include <iostream>
#include <fstream>

void solve1(std::string&& filename) {

    std::cout << filename << ":\t";

    std::string row;
    std::ifstream input{filename};
    std::getline(input, row);
    input.seekg(0);
    int n_row, n_column = row.size();
    for (n_row = -1; input; ++n_row) std::getline(input, row);

    int trees[n_row][n_column];
    int lefts[n_row][n_column];
    int rights[n_row][n_column];
    int ups[n_row][n_column];
    int downs[n_row][n_column];

    input.clear();
    input.seekg(0);

    // trees
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_column + 1; ++j) {
            char c;
            input.get(c);
            if (c >= '0' && c <= '9') {
                trees[i][j] = int(c - '0');
            }
        }
    }

    // lefts
    for (int i = 0; i < n_row; ++i) {
        int max = 0;
        for (int j = 0; j < n_column; ++j ) {
            lefts[i][j] = max;
            max = max > trees[i][j] ? max : trees[i][j];
        }
    }

    // rights
    for (int i = 0; i < n_row; ++i) {
        int max = 0;
        for (int j = n_column-1; j >= 0; --j ) {
            rights[i][j] = max;
            max = max > trees[i][j] ? max : trees[i][j];
        }
    }

    // downs
    for (int j = 0; j < n_column; ++j ) {
        int max = 0;
        for (int i = 0; i < n_row; ++i) {
            downs[i][j] = max;
            max = max > trees[i][j] ? max : trees[i][j];
        }
    }

    // ups
    for (int j = 0; j < n_column; ++j ) {
        int max = 0;
        for (int i = n_row-1; i >= 0; --i) {
            ups[i][j] = max;
            max = max > trees[i][j] ? max : trees[i][j];
        }
    }

    int count = 4 + 2*(n_row-2) + 2*(n_column-2);
    for (int i = 1; i < n_row-1; ++i) {
        for (int j = 1; j < n_column-1; ++j ) {
            if (trees[i][j] > ups[i][j] ||
                trees[i][j] > downs[i][j] ||
                trees[i][j] > rights[i][j] ||
                trees[i][j] > lefts[i][j]) {
                count++;
            }
        }
    }

    //for (int i = 0; i < n_row; ++i) {
        //for (int j = 0; j < n_column; ++j ) {
            //std::cout << "("
                //<< trees[i][j] << ":"
                //<< lefts[i][j]
                //<< rights[i][j]
                //<< downs[i][j]
                //<< ups[i][j] << ") ";
        //}
        //std::cout << std::endl;
    //}

    int solution = count;
    std::cout << "1: " << solution << std::endl;
}

void solve2(std::string&& filename) {
    std::cout << filename << ":\t";

    std::string row;
    std::ifstream input{filename};
    std::getline(input, row);
    input.seekg(0);
    int n_row, n_column = row.size();
    for (n_row = -1; input; ++n_row) std::getline(input, row);

    int trees[n_row][n_column];

    input.clear();
    input.seekg(0);

    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_column + 1; ++j) {
            char c;
            input.get(c);
            if (c >= '0' && c <= '9') {
                trees[i][j] = int(c - '0');
            }
        }
    }

    int solution = 0;
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_column; ++j ) {

            int total = 1;
            int count = 0;
            for (int k = i+1; k < n_row; ++k) {
                count += 1;
                if (trees[i][j] <= trees[k][j]) {
                    break;
                }
            }
            total *= count;

            count = 0;
            for (int k = i-1; k >= 0; --k) {
                count += 1;
                if (trees[i][j] <= trees[k][j]) {
                    break;
                }
            }
            total *= count;

            count = 0;
            for (int k = j+1; k < n_column; ++k) {
                count += 1;
                if (trees[i][j] <= trees[i][k]) {
                    break;
                }
            }
            total *= count;

            count = 0;
            for (int k = j-1; k >= 0; --k) {
                count += 1;
                if (trees[i][j] <= trees[i][k]) {
                    break;
                }
            }
            total *= count;

            solution = total > solution ? total : solution;
        }
    }

    std::cout << "2: " << solution << std::endl;
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    solve2("input/" + day + ".test");
    solve2("input/" + day + ".in");
}
