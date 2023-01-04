#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <iomanip>

#define MAX_SIZE 200

class Map {
public:
    Map (std::string filename, char start_, char end_, bool increase_) :
        n_row{0},
        n_col{0},
        start_x{0},
        start_y{0},
        start_level{' '},
        start{start_},
        end{end_},
        increase{increase_} {
            if (start == 'S') {
                start_level = 'a';
            } else if (start == 'E') {
                start_level = 'z';
            }

            std::ifstream input(filename);
            char c;
            while (input.get(c)) {
                if (c == '\n') n_row++;
                else n_col++;
            }  n_col /= n_row;


            input.clear();
            input.seekg(0);

            for (int y = 0; y < n_row; ++y) {
                for (int x = 0; x < n_col+1; ++x) {

                    input.get(c);
                    if (c != '\n') {
                        map[y][x] = c;
                    }

                    if (c == start) {
                        start_x = x;
                        start_y = y;
                    }
                }
            }

            // set visited to INT_MAX
            for (int i = 0; i < n_row; ++i)
                for (int j = 0; j < n_col; ++j)
                    visited[i][j] = INT_MAX;

            // set trace to 0
            for (int i = 0; i < n_row; ++i)
                for (int j = 0; j < n_col; ++j)
                    trace[i][j] = ' ';
        }
    virtual ~Map () {}

    bool step(char curr, char next) {
        bool okey = curr >= 'a' && curr <= 'z' && next >= 'a' && next <= 'z';
        if (increase) {
            return (okey && next <= curr+1) || (curr >= 'y' && next == end);
        } else {
            return okey && curr <= next+1;
        }
    }

    void print_debug() {
        std::cout.fill(' ');
        for (int i = 0; i < n_row; ++i) {
            for (int j = 0; j < n_col; ++j) {
                if (visited[i][j] != INT_MAX) {
                    std::cout << std::setw(4) << visited[i][j] << ":" << trace[i][j];
                } else {
                    std::cout << std::setw(6) << 0;
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    int traverse(int x, int y, int distance, char c) {
        visited[y][x] = distance;
        trace[y][x] = c;

        if (c == end) {
            return distance;
        }

        int shortest = INT_MAX;
        char new_c = map[y][x+1];
        if (x+1<n_col && step(c, new_c) && distance+1 < visited[y][x+1]) {
            int c = traverse(x+1, y, distance+1, new_c);
            shortest = c < shortest ? c : shortest;
        }

        new_c = map[y][x-1];
        if (x-1>=0 && step(c, new_c) && distance+1 < visited[y][x-1]) {
            int c = traverse(x-1, y, distance+1, new_c);
            shortest = c < shortest ? c : shortest;
        }

        new_c = map[y+1][x];
        if (y+1<n_row && step(c, new_c) && distance+1 < visited[y+1][x]) {
            int c = traverse(x, y+1, distance+1, new_c);
            shortest = c < shortest ? c : shortest;
        }

        new_c = map[y-1][x];
        if (y-1>=0 && step(c, new_c) && distance+1 < visited[y-1][x]) {
            int c = traverse(x, y-1, distance+1, new_c);
            shortest = c < shortest ? c : shortest;
        }

        return shortest;
    }

    int solve() {
        return traverse(start_x, start_y, 0, start_level);
    }

private:
    int n_row, n_col;
    int start_x, start_y;
    char start, end;
    bool increase;
    char map[MAX_SIZE][MAX_SIZE];
    char trace[MAX_SIZE][MAX_SIZE];
    int visited[MAX_SIZE][MAX_SIZE];
    char start_level;
};

void solve1(std::string&& filename) {
    std::cout << filename << ":\t";

    Map map(filename, 'S', 'E', true);
    std::cout << "1: " << map.solve() << std::endl;

    //map.print_debug();
}

void solve2(std::string&& filename) {
    std::cout << filename << ":\t";

    Map map(filename, 'E', 'a', false);
    std::cout << "2: " << map.solve() << std::endl;

    //map.print_debug();
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    solve2("input/" + day + ".test");
    solve2("input/" + day + ".in");
}
