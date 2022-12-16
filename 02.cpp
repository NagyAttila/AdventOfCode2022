#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

void solve1(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ": ";

    std::ifstream input{filename};
    while (input) {
        std::string s;
        std::getline(input, s);

        int score = 0;

        if (s.empty()) {
            continue;
        }

        if (s[2] == 'X') {
            score += 1;
            if (s[0] == 'A') { score += 3; }
            if (s[0] == 'C') { score += 6; }
        } else if (s[2] == 'Y') {
            score += 2;
            if (s[0] == 'B') { score += 3; }
            if (s[0] == 'A') { score += 6; }
        } else if (s[2] == 'Z') {
            score += 3;
            if (s[0] == 'C') { score += 3; }
            if (s[0] == 'B') { score += 6; }
        }

        solution += score;
    }

    std::cout << "1: " << solution << std::endl;
}

void solve2(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ": ";

    std::ifstream input{filename};
    while (input) {
        std::string s;
        std::getline(input, s);

        int score = 0;

        if (s.empty()) {
            continue;
        }

        if (s[2] == 'X') {
            score += 0;
            if (s[0] == 'A') { score += 3; }
            if (s[0] == 'B') { score += 1; }
            if (s[0] == 'C') { score += 2; }
        } else if (s[2] == 'Y') {
            score += 3;
            if (s[0] == 'A') { score += 1; }
            if (s[0] == 'B') { score += 2; }
            if (s[0] == 'C') { score += 3; }
        } else if (s[2] == 'Z') {
            score += 6;
            if (s[0] == 'A') { score += 2; }
            if (s[0] == 'B') { score += 3; }
            if (s[0] == 'C') { score += 1; }
        }

        solution += score;
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
