#include <fstream>
#include <vector>
#include <iostream>
#include <numeric>
#include <unordered_map>

int main(int argc, char* argv[]) {   
    std::ifstream inFile("./data.txt");

    if (inFile.is_open()) {
        const std::unordered_map<std::string, uint32_t> pointMap{
            {"A X", 4},
            {"A Y", 8},
            {"A Z", 3},
            {"B X", 1},
            {"B Y", 5},
            {"B Z", 9},
            {"C X", 7},
            {"C Y", 2},
            {"C Z", 6}
        };
        std::vector<std::string> rounds{};
        for (std::string line; std::getline(inFile, line);) { if (line.length() > 3) line.erase(line.length()-1); rounds.push_back(line); }
        uint32_t sum = std::accumulate(rounds.begin(), rounds.end(), 0, [&pointMap](uint32_t sum, std::string s) {
            if (auto search = pointMap.find(s); search != pointMap.end()) return sum + search->second;
            else return sum;
        });
        std::cout << sum << std::endl;
    } 
    return 0;
}
