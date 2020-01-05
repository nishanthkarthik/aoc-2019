#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <functional>

int massToFuel(int mass) {
    return (mass / 3) - 2;
}

int massToFuelLoop(int mass) {
    auto fuel = massToFuel(mass);
    auto sum = 0;
    while (fuel > 0) {
        sum += fuel;
        fuel = massToFuel(fuel);
    }
    return sum;
}

std::vector<int> readInput(std::string_view fileName) {
    std::ifstream in{fileName.data()};
    std::vector<int> lines;
    for (int line; in >> line;) {
        lines.emplace_back(line);
    }
    return lines;
}

template<typename T>
int calculateFuel(T fn) {
    const auto masses = readInput("input");
    std::vector<int> fuels(masses.size());
    std::transform(masses.begin(), masses.end(), fuels.begin(), fn);
    const auto totalFuel = std::accumulate(fuels.begin(), fuels.end(), 0);
    return totalFuel;
}

int main() {
    std::cout << "First fuel : " << calculateFuel(massToFuel) << std::endl;
    std::cout << "Second fuel : " << calculateFuel(massToFuelLoop) << std::endl;
}
