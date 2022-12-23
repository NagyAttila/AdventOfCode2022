#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <deque>        // std::deque
#include <stack>        // std::stack
#include <numeric>      // std::iota
#include <map>

int solve(std::string& filename, const int length_or_marker) {
    int solution;
    std::ifstream input{filename};
    while (input) {
        std::string line;
        std::getline(input, line);

        if (line.empty()) {
            continue;
        }

        std::deque<char> d;
        solution = length_or_marker;
        for (const char c : line) {
            d.push_back(c);

            if (d.size() > length_or_marker) {
                d.pop_front();
            } else if (d.size() < length_or_marker) {
                continue;
            }

            if (d.size() == length_or_marker) {
                bool b = false;
                for (int i = 0; i < length_or_marker; ++i) {
                    for (int j = i+1; j < length_or_marker; ++j) {
                        if (d[i] == d[j]) {
                            b = true;
                            solution++;
                            break;
                        }
                    }
                    if (b) { break; }
                }

                if (!b) {
                    std::cout << "(";
                    for (const auto c : d) {
                        std::cout << c;
                    }
                    std::cout << ") ";
                    break;
                }
            }
        }
    }

    return solution;
}

void solve1(std::string&& filename) {
    std::cout << filename << ":\t1: " << solve(filename, 4) << std::endl;
}

void solve2(std::string&& filename) {
    std::cout << filename << ":\t2: " << solve(filename, 14) << std::endl;
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    solve2("input/" + day + ".test");
    solve2("input/" + day + ".in");
}
