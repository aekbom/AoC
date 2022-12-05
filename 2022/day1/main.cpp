#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>

int main(int argc, char* argv[]) {   
    std::ifstream inFile("./data.txt");

    if (inFile.is_open()) {
        std::vector<uint32_t> sums{};
        uint32_t sum = 0;
        std::string ss;
        while (std::getline(inFile, ss)) {
            if (ss.length() > 1) sum += std::stoi(ss);
            else {
                sums.push_back(sum);
                sum = 0;
            }
        }
        std::sort(sums.begin(), sums.end());
        auto sumOfLast3Elves = std::reduce(sums.end() - 3, sums.end());

        std::cout << "The sum of the fattest 3 elves " << sumOfLast3Elves << std::endl;
    } 
    
    return 0;
}
