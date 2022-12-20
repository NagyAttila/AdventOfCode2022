#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <numeric>      // std::iota

void solve1(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ":\t";

    std::ifstream input{filename};
    while (input) {
        std::string line;
        std::getline(input, line);

        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string l1, l2, r1, r2;

        std::getline(iss, l1, '-');
        std::getline(iss, l2, ',');
        std::getline(iss, r1, '-');
        std::getline(iss, r2);

        if ((std::stoi(l1) >= std::stoi(r1) && std::stoi(l2) <= std::stoi(r2)) ||
            (std::stoi(r1) >= std::stoi(l1) && std::stoi(r2) <= std::stoi(l2))) {
            solution += 1;
        }
    }

    std::cout << "1: " << solution << std::endl;
}

void solve2(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ":\t";

    std::ifstream input{filename};
    while (input) {
        std::string line;
        std::getline(input, line);

        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string l1, l2, r1, r2;

        std::getline(iss, l1, '-');
        std::getline(iss, l2, ',');
        std::getline(iss, r1, '-');
        std::getline(iss, r2);

        if ((std::stoi(l1) >= std::stoi(r1) && std::stoi(l1) <= std::stoi(r2)) ||
            (std::stoi(l2) >= std::stoi(r1) && std::stoi(l2) <= std::stoi(r2)) ||
            (std::stoi(r1) >= std::stoi(l1) && std::stoi(r1) <= std::stoi(l2)) ||
            (std::stoi(r2) >= std::stoi(l1) && std::stoi(r2) <= std::stoi(l2))) {
            solution += 1;
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
