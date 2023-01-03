#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <iomanip>

#define MAX_SIZE 200

int n_row = 0, n_col = 0;

int trace[MAX_SIZE][MAX_SIZE] = {};
int visited[MAX_SIZE][MAX_SIZE] = {};

void clear_map(int map[MAX_SIZE][MAX_SIZE], int v) {
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_col; ++j) {
            map[i][j] = v;
        }
    }
}

void print_trace(int map[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_col; ++j) {
            if (map[i][j]) {
                std::cout << (char)map[i][j];
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_visited(int map[MAX_SIZE][MAX_SIZE]) {
    for (int i = 0; i < n_row; ++i) {
        for (int j = 0; j < n_col; ++j) {
            if (map[i][j] != INT_MAX) {
                std::cout << std::setw(3) << map[i][j] << " " ;
            } else {
                std::cout << std::setw(3) << 0 << " " ;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool step(char curr, char next) {
    return  curr+1 >= next || (curr == 'z' && next == 'E');
}

int traverse(char map[MAX_SIZE][MAX_SIZE], int x, int y, int distance, char c) {
    visited[y][x] = distance;
    trace[y][x] = c;

    if (c == 'E') {
        return distance;
    }

    int shortest = INT_MAX;
    char new_c = map[y][x+1];
    if (x+1<n_col && step(c, new_c) && distance+1 < visited[y][x+1]) {
        int c = traverse(map, x+1, y, distance+1, new_c);
        shortest = c < shortest ? c : shortest;
    }

    new_c = map[y][x-1];
    if (x-1>=0 && step(c, new_c) && distance+1 < visited[y][x-1]) {
        int c = traverse(map, x-1, y, distance+1, new_c);
        shortest = c < shortest ? c : shortest;
    }

    new_c = map[y+1][x];
    if (y+1<n_row && step(c, new_c) && distance+1 < visited[y+1][x]) {
        int c = traverse(map, x, y+1, distance+1, new_c);
        shortest = c < shortest ? c : shortest;
    }

    new_c = map[y-1][x];
    if (y-1>=0 && step(c, new_c) && distance+1 < visited[y-1][x]) {
        int c = traverse(map, x, y-1, distance+1, new_c);
        shortest = c < shortest ? c : shortest;
    }

    return shortest;
}

void solve1(std::string&& filename) {
    std::cout << filename << ":\n";

    std::cout.fill('0');

    std::ifstream input(filename);
    char c;
    while (input.get(c)) {
        if (c == '\n') n_row++;
        else n_col++;
    }  n_col /= n_row;


    char map[MAX_SIZE][MAX_SIZE] = {};

    input.clear();
    input.seekg(0);

    int s_x = 0, s_y = 0;
    for (int y = 0; y < n_row; ++y) {
        for (int x = 0; x < n_col+1; ++x) {

            input.get(c);
            if (c != '\n') {
                map[y][x] = c;
            }

            if (c=='S') {
                s_x = x;
                s_y = y;
            }
        }
    }

    clear_map(visited, INT_MAX);
    clear_map(trace, ' ');
    int solution = traverse(map, s_x, s_y, 0, 'a');
    print_trace(trace);

    std::cout << "1: " << solution << std::endl;
}

void solve2(std::string&& filename) {
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    //solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    //solve2("input/" + day + ".test");
    //solve2("input/" + day + ".in");
}
