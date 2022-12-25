#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define MAP_SIZE 500

void solve1(std::string&& filename) {
    std::cout << filename << ":\t";

    bool tail[MAP_SIZE][MAP_SIZE] = {};

    int tail_x, tail_y, head_x, head_y;
    tail_x = tail_y = head_x = head_y = MAP_SIZE/2;

    std::string line;
    std::ifstream input(filename);
    while (std::getline(input, line)) {

        // get number
        std::string times;
        std::istringstream ss(line);
        std::getline(ss, times, ' ');
        std::getline(ss, times);

        for (int i = 0; i < std::stoi(times); ++i) {
            // update head
            if (line[0] == 'U') {
                head_y--;
            } else if (line[0] == 'D') {
                head_y++;
            } else if (line[0] == 'L') {
                head_x--;
            } else if (line[0] == 'R') {
                head_x++;
            }

            // update tail
            if (head_y - tail_y > 1) {
                tail_y++;
                if (head_x - tail_x > 0) tail_x++;
                if (head_x - tail_x < 0) tail_x--;
            }

            if (head_y - tail_y < -1) {
                tail_y--;
                if (head_x - tail_x > 0) tail_x++;
                if (head_x - tail_x < 0) tail_x--;
            }

            if (head_x - tail_x > 1) {
                tail_x++;
                if (head_y - tail_y > 0) tail_y++;
                if (head_y - tail_y < 0) tail_y--;
            }

            if (head_x - tail_x < -1) {
                tail_x--;
                if (head_y - tail_y > 0) tail_y++;
                if (head_y - tail_y < 0) tail_y--;
            }

            tail[tail_y][tail_x] = true;
        }
    }

    int solution = 0;
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            if (tail[i][j]) {
                solution++;
            }
            //std::cout << tail[i][j];
        }
        //std::cout << std::endl;
    }

    std::cout << "1: " << solution << std::endl;
}

#define N_KNOTS 10
void solve2(std::string&& filename) {
    std::cout << filename << ":\t";

    bool tail[MAP_SIZE][MAP_SIZE] = {};

    int xs[N_KNOTS]; for (int i = 0; i<N_KNOTS; i++) xs[i] = MAP_SIZE/2;
    int ys[N_KNOTS]; for (int i = 0; i<N_KNOTS; i++) ys[i] = MAP_SIZE/2;

    std::string line;
    std::ifstream input(filename);
    while (std::getline(input, line)) {

        // get number
        std::string times;
        std::istringstream ss(line);
        std::getline(ss, times, ' ');
        std::getline(ss, times);

        for (int i = 0; i < std::stoi(times); ++i) {
            // update head
            if (line[0] == 'U') {
                ys[0]--;
            } else if (line[0] == 'D') {
                ys[0]++;
            } else if (line[0] == 'L') {
                xs[0]--;
            } else if (line[0] == 'R') {
                xs[0]++;
            }

            // update tail knots
            for (int i = 1; i < N_KNOTS; ++i) {
                if (ys[i-1] - ys[i] > 1) {
                    ys[i]++;
                    if (xs[i-1] - xs[i] > 0) xs[i]++;
                    if (xs[i-1] - xs[i] < 0) xs[i]--;
                }

                if (ys[i-1] - ys[i] < -1) {
                    ys[i]--;
                    if (xs[i-1] - xs[i] > 0) xs[i]++;
                    if (xs[i-1] - xs[i] < 0) xs[i]--;
                }

                if (xs[i-1] - xs[i] > 1) {
                    xs[i]++;
                    if (ys[i-1] - ys[i] > 0) ys[i]++;
                    if (ys[i-1] - ys[i] < 0) ys[i]--;
                }

                if (xs[i-1] - xs[i] < -1) {
                    xs[i]--;
                    if (ys[i-1] - ys[i] > 0) ys[i]++;
                    if (ys[i-1] - ys[i] < 0) ys[i]--;
                }

                if (i == N_KNOTS-1) {
                    tail[ys[i]][xs[i]] = true;
                }
            }
        }
    }

    int solution = 0;
    for (int i = 0; i < MAP_SIZE; ++i) {
        for (int j = 0; j < MAP_SIZE; ++j) {
            if (tail[i][j]) {
                solution++;
            }
            //std::cout << tail[i][j];
        }
        //std::cout << std::endl;
    }

    std::cout << "2: " << solution << std::endl;
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    solve2("input/" + day + ".test");
    solve2("input/" + day + ".test2");
    solve2("input/" + day + ".in");
}
