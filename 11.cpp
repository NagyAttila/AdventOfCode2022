#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <deque>
#include <functional>
#include <algorithm>

void solve(std::string&& filename, int part) {
    std::cout << filename << ":\t";

    std::map<int,std::deque<long>> items;
    std::map<int,std::string> operations;
    std::map<int,int> tests;
    std::map<int,int> if_true;
    std::map<int,int> if_false;

    std::string line;
    std::ifstream input(filename);
    int monkey;
    while (std::getline(input, line)) {

        std::istringstream ss(line);
        if (line[0] == 'M') {
            monkey = line[7] - '0';
        } else if (line.substr(0,3) == "  S") {
            std::string item;
            std::getline(ss, item, ':');
            while (std::getline(ss, item, ',')) {
                if (items.find(monkey) == items.end()) {
                    items.insert({monkey, std::deque<long>()});
                }
                items[monkey].push_back(std::stoi(item));
            }
        } else if (line.substr(0,3) == "  O") {
            operations.insert({monkey, line.substr(19)});
        } else if (line.substr(0,3) == "  T") {
            tests.insert({monkey, std::stoi(line.substr(21))});
        } else if (line.substr(0,8) == "    If t") {
            if_true.insert({monkey, std::stoi(line.substr(28))});
        } else if (line.substr(0,8) == "    If f") {
            if_false.insert({monkey, std::stoi(line.substr(29))});
        }
    }

    int test_prod = 1;
    for (const auto t : tests) {
        test_prod *= t.second;
    }

    int n_rounds;
    if (part == 1) n_rounds = 21;
    else if (part == 2) n_rounds = 10001;

    std::map<int,int> inspections;
    for (int round = 1; round < n_rounds; ++round) {
        for (auto& m : items) {
            auto& monkey_items = m.second;
            const auto monkey_id = m.first;

            while (monkey_items.size()) {
                std::string op;
                std::istringstream ss(operations[monkey_id]);
                std::function f = [](long a, long b) {return a+b;};
                long result = 0;
                while (std::getline(ss, op, ' ')) {
                    if (op == "old") {
                        result = f(result, monkey_items.front());
                    } else if (op[0] == '*') {
                        f = [](long a, long b) {return a*b;};
                    } else if (op[0] == '+') {
                        f = [](long a, long b) {return a+b;};
                    } else {
                        result = f(result, std::stoi(op));
                    }
                }

                if (part == 1) result /= 3;
                else if (part == 2) result %= test_prod;

                //bool tf = result % tests[monkey_id] == 0;
                //std::cout << "monkey=" << monkey_id << " "
                          //<< "item=" << monkey_items.front() << " "
                          //<< "op=" << operations[monkey_id] << " "
                          //<< "result=" << result << " "
                          //<< "test=" << tests[monkey_id] << " "
                          //<< "true/false=" << tf << " "
                          //<< "to=" << (tf ? if_true[monkey_id] : if_false[monkey_id]) << std::endl;

                if (result % tests[monkey_id] == 0) {
                    items[if_true[monkey_id]].push_back(result);
                } else {
                    items[if_false[monkey_id]].push_back(result);
                }
                monkey_items.pop_front();

                if (inspections.find(monkey_id) == inspections.end()) {
                    inspections.insert({monkey_id, 1});
                } else {
                    inspections[monkey_id]++;
                }
            }
        }
    }

    std::vector<long> v;
    for (auto i : inspections) {
        v.push_back(i.second);
    }
    std::sort(v.begin(), v.end(), [](long a, long b){return a>b;});
    long solution = v[0] * v[1];

    std::cout << part << ": " << solution << std::endl;
}

int main(int argc, char *argv[]) {
    std::string day(argv[1]);

    solve("input/" + day + ".test", 1);
    solve("input/" + day + ".in", 1);
    solve("input/" + day + ".test", 2);
    solve("input/" + day + ".in", 2);
}
