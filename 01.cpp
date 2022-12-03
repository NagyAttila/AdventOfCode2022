#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

int main() {
    std::ifstream input{"input/01.in"};

    std::vector<long> v;
    long acc = 0;
    while (input) {
        std::string s;
        std::getline(input, s);
        if (!s.empty()) {
            acc += stoi(s);
        } else {
            v.push_back(acc);
            acc = 0;
        }
    }

    std::sort(v.begin(), v.end());

    std::cout << "1: " << v.back() << std::endl;

    acc = 0;
    for (int i = 1; i < 4; ++i) {
        acc += *(v.end()-i);
    }
    std::cout << "2: " << acc << std::endl;
}
