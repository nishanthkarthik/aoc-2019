#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <type_traits>

enum class Instr {
    Add = 1,
    Mul = 2,
    Halt = 99
};

template<typename T>
void printVector(const std::vector<T> &v) {
    for (const auto e : v) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

std::vector<std::string> splitStr(std::string src, char delim) {
    std::vector<std::string> strings;
    size_t pos = 0;
    std::string token;
    while((pos = src.find(delim)) != std::string::npos) {
        strings.emplace_back(src.substr(0, pos));
        src.erase(0, pos + 1);
    }
    return strings;
}

std::vector<int> readInput(std::string_view fileName) {
    std::ifstream in{fileName.data()};
    std::string line;
    in >> line;
    const auto terms = splitStr(line, ',');
    std::vector<int> ops(terms.size());
    std::transform(terms.begin(), terms.end(), ops.begin(), [](const auto s) { return std::stoi(s); });
    return ops;
}

void evalOpCodes(std::vector<int> &mem) {
    unsigned pc = 0;
    using unsgnd = std::make_unsigned_t<int>;
    while (pc < mem.size()) {
        const Instr op = static_cast<Instr>(mem[pc]);
        switch (op) {
        case Instr::Halt:
            return;
        case Instr::Add:
            mem[unsgnd(mem[pc + 3])] = mem[unsgnd(mem[pc + 1])] + mem[unsgnd(mem[pc + 2])];
            pc += 4;
            break;
        case Instr::Mul:
            mem[unsgnd(mem[pc + 3])] = mem[unsgnd(mem[pc + 1])] * mem[unsgnd(mem[pc + 2])];
            pc += 4;
            break;
        }
    }
}

void test(std::vector<int> ops, std::vector<int> expected) {
    std::cout << "From ";
    printVector(ops);
    evalOpCodes(ops);
    std::cout << "To   ";
    printVector(ops);
    std::cout << "Result " << (ops == expected) << std::endl;
}

void tests() {
    test({1,0,0,0,99}, {2,0,0,0,99});
    test({2,3,0,3,99}, {2,3,0,6,99});
    test({2,4,4,5,99,0}, {2,4,4,5,99,9801});
    test({1,1,1,4,99,5,6,0,99}, {30,1,1,4,2,5,6,0,99});
}

void first() {
    auto terms = readInput("input");
    terms[1] = 12;
    terms[2] = 2;
    evalOpCodes(terms);
    std::cout << "First " << terms[0] << std::endl;
}

void second() {
    auto terms = readInput("input");
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            auto memory = terms;
            memory[1] = i;
            memory[2] = j;
            evalOpCodes(memory);
            if (memory[0] == 19690720) {
                std::cout << "Solution " << i << ", " << j << std::endl;
                return;
            }
        }
    }
}

int main() {
    first();
    second();
    return 0;
}
