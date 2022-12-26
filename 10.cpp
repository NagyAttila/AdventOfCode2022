#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void solve1(std::string&& filename) {
    std::cout << filename << ":\t";

    int solution = 0;
    int cycle = 1;
    int x = 1;

    std::string line;
    std::ifstream input(filename);
    while (std::getline(input, line)) {

        if (line[0] == 'n') { // noop
            cycle++;
        } else if (line[0] == 'a') { // addx

            // get number
            std::string times;
            std::istringstream ss(line);
            std::getline(ss, times, ' ');
            std::getline(ss, times);

            cycle++;
            if ((cycle-20)%40 == 0) {
                solution += x*cycle;
            }

            cycle++;
            x += std::stoi(times);
        }

        if ((cycle-20)%40 == 0) {
            solution += x*cycle;
        }
    }

    std::cout << "1: " << solution << std::endl;
}

#define SCREEN_SIZE 240
bool is_covered(int x, int cycle) {
    x++; cycle++;
    return x <= cycle%40 && x+2 >= cycle%40;;
}

void solve2(std::string&& filename) {
    std::cout << filename << ":\t2:" << std::endl;

    int solution = 0;
    int cycle = 0;
    int x = 0;

    char screen[SCREEN_SIZE] = {};
    screen[cycle] = is_covered(x, cycle) ? '#' : '.';

    std::string line;
    std::ifstream input(filename);
    while (std::getline(input, line)) {

        if (line[0] == 'n') { // noop
            cycle++;
            screen[cycle] = is_covered(x, cycle) ? '#' : '.';
        } else if (line[0] == 'a') { // addx

            // get number
            std::string times;
            std::istringstream ss(line);
            std::getline(ss, times, ' ');
            std::getline(ss, times);

            cycle++;
            screen[cycle] = is_covered(x, cycle) ? '#' : '.';
            cycle++;
            x += std::stoi(times);
            screen[cycle] = is_covered(x, cycle) ? '#' : '.';
        }
    }

    for (int i = 0; i < SCREEN_SIZE; ++i) {
        std::cout << screen[i];

        if ((i+1) % 40 == 0) {
            std::cout << std::endl;
        }
    }
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    solve2("input/" + day + ".test");
    solve2("input/" + day + ".in");
}
