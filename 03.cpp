#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include <numeric>      // std::iota

void solve1(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ": ";

    // Creating priority list
    char albet[52] {};
    std::iota(std::begin(albet), std::begin(albet)+26, 'a');
    std::iota(std::begin(albet)+26, std::end(albet), 'A');
    const std::string prio(albet);

    std::ifstream input{filename};
    while (input) {
        std::string s;
        std::getline(input, s);

        int score = 0;

        if (s.empty()) {
            continue;
        }

        std::string intersection;
        int size = s.size() / 2;
        std::string s1 = std::string(s.begin(), s.begin()+size);
        std::string s2 = std::string(s.begin()+size, s.end());
        std::sort(s1.begin(), s1.end());
        std::sort(s2.begin(), s2.end());
        std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(intersection));

        solution += prio.find(intersection[0]) + 1;

        // std::cout << s1 << " " << s2 << " " << intersection << i << std::endl;
    }

    std::cout << "1: " << solution << std::endl;
}

void solve2(std::string&& filename) {
    long solution = 0;

    std::cout << filename << ": ";

    // Creating priority list
    char albet[52] {};
    std::iota(std::begin(albet), std::begin(albet)+26, 'a');
    std::iota(std::begin(albet)+26, std::end(albet), 'A');
    const std::string prio(albet);

    int c = 1;
    std::string s1, s2, s3;

    std::ifstream input{filename};
    while (input) {
        std::string s;
        std::getline(input, s);

        int score = 0;

        if (s.empty()) {
            continue;
        }

        if (c==1) {
            s1 = std::string(s.begin(), s.end());
            std::sort(s1.begin(), s1.end());
            c++;
        } else if (c==2) {
            s2 = std::string(s.begin(), s.end());
            std::sort(s2.begin(), s2.end());
            c++;
        } else if (c==3) {
            s3 = std::string(s.begin(), s.end());
            std::sort(s3.begin(), s3.end());
            c = 1;

            std::string intersection;
            std::set_intersection(s1.begin(), s1.end(),
                                  s2.begin(), s2.end(),
                                  std::back_inserter(intersection));

            std::string final_intersection;
            std::set_intersection(intersection.begin(), intersection.end(),
                                  s3.begin(), s3.end(),
                                  std::back_inserter(final_intersection));

            solution += prio.find(final_intersection[0]) + 1;

            // std::cout << s1 << " " << s2 << " " << s3 << " " << final_intersection << i << std::endl;
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
