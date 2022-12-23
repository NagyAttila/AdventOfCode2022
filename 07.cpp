#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>    // std::sort
#include <deque>        // std::deque
#include <stack>        // std::stack
#include <numeric>      // std::iota
#include <vector>
#include <functional>
#include <map>

struct Element {
    Element* parent;
    std::vector<Element*> children;
    long size;
    std::string name;
};

long solution_1 = 0;
long traverse_1(Element* e) {
    long total = e->size;
    for (const auto child : e->children) {
        long candidate = traverse_1(child);
        if (child->size == 0 && candidate <= 100000) {
            solution_1 += candidate;
        }
        total += candidate;
    }
    return total;
}

long solution_2 = 0;
long traverse_2(Element* e, const long needed) {
    long total = e->size;
    for (const auto child : e->children) {
        long candidate = traverse_2(child, needed);
        if (child->size == 0 && candidate >= needed && candidate < solution_2) {
            solution_2 = candidate;
        }
        total += candidate;
    }
    return total;
}

long get_total(Element* e) {
    long total = e->size;
    for (const auto child : e->children) {
        total += get_total(child);;
    }
    return total;
}

Element create_tree(std::string filename) {
    Element root{nullptr, std::vector<Element*>(), 0, "/"};
    Element* current = &root;
    std::ifstream input{filename};
    while (input) {
        std::string line;
        std::getline(input, line);

        if (line.empty()) {
            continue;
        }

        std::istringstream isrow(line);
        if (line.substr(0,4) == "$ cd") {
            std::string dir_name;
            std::getline(isrow, dir_name, ' ');
            std::getline(isrow, dir_name, ' ');
            std::getline(isrow, dir_name);

            if (dir_name == "/") {
                current = &root;
            } else if (dir_name == "..") {
                current = current->parent;
            } else {
                for (const auto child : current->children) {
                    if (child->name == dir_name) {
                        current = child;
                        break;
                    }
                }
            }

        } else if (line.substr(0,4) == "$ ls") {
        } else if (line.substr(0,3) == "dir") {
                std::string dir_name;
                std::getline(isrow, dir_name, ' ');
                std::getline(isrow, dir_name);

                current->children.push_back(
                        new Element{current, std::vector<Element*>(), 0, dir_name});
        } else {
            std::string file_size;
            std::getline(isrow, file_size, ' ');

            std::string file_name;
            std::getline(isrow, file_name);
            current->children.push_back(
                    new Element{current, std::vector<Element*>(), std::stoi(file_size), file_name});
        }
    }
    return root;
}

void solve1(std::string&& filename) {

    std::cout << filename << ":\t";

    Element root = create_tree(filename);

    solution_1 = 0;
    traverse_1(&root);

    std::cout << "1: " << solution_1 << std::endl;
}

void solve2(std::string&& filename) {
    std::cout << filename << ":\t";

    Element root = create_tree(filename);

    const long total = solution_2 = get_total(&root);
    const long unused = 70000000 - total;
    const long needed = 30000000 - unused;
    traverse_2(&root, needed);

    std::cout << "2: " << solution_2 << std::endl;
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve1("input/" + day + ".test");
    solve1("input/" + day + ".in");
    solve2("input/" + day + ".test");
    solve2("input/" + day + ".in");
}
