#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <deque>        // std::deque
#include <numeric>      // std::iota
#include <map>


void solve1(std::string&& filename) {
    std::string solution;

    std::cout << filename << ":\t";

    std::map<int,std::deque<char>> crates;
    std::ifstream input{filename};
    bool end_of_header = false;
    while (input) {
        std::string line;
        std::getline(input, line);

        if (line.empty()) {
            continue;
        }

        end_of_header = line.find('[') == std::string::npos;
        if (!end_of_header) {
            int column = 1;
            for (int i = 1; i < line.size(); i+=4) {
                if (line[i] != ' ') {
                    if (crates.find(column) == crates.end()) {
                        crates.emplace(column, std::deque<char>());
                    }
                    crates[column].push_back(line[i]);
                }
                column++;
            }
        } else if (line[0] == 'm') {
            std::istringstream iss(line.substr(5));
            std::string n, f, t;

            std::getline(iss, n, ' ');
            std::getline(iss, f, ' ');
            std::getline(iss, f, ' ');
            std::getline(iss, t, ' ');
            std::getline(iss, t);

            for (int i = 0; i < std::stoi(n); ++i) {
                crates[std::stoi(t)].push_front(crates[std::stoi(f)].front());
                crates[std::stoi(f)].pop_front();
            }

            //for (auto const &pair: crates) { std::cout << pair.first; for (auto const &e: pair.second) { std::cout << e; } } std::cout << std::endl;
        }
    }

    if (crates.size()) {
        for (int i = 1; i < crates.size() + 1; ++i) {
         solution += crates[i].front();
        }
    }

    std::cout << "1: " << solution << std::endl;
}

void solve2(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ":\t";

    std::cout << "2: " << solution << std::endl;
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    //solve2("input/" + day + ".test");
    //solve2("input/" + day + ".in");
}
