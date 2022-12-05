#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <chrono>

int main(int argc, char* argv[]) {   
    //auto t1 = std::chrono::high_resolution_clock::now();
    std::ifstream inFile("./data.txt");

    if (inFile.is_open()) {
        std::vector<std::string> rucksacks;
        uint32_t sum{0};
        for (std::string line; std::getline(inFile, line);) rucksacks.push_back(line.substr(0, line.find('\r')));
        for (auto it = rucksacks.begin() + 2; it < rucksacks.end(); it += 3) {
            auto badge = std::find_if(it->begin(), it->end(), [&](char& c) {
                return ((it-1)->find(c) != std::string::npos && (it-2)->find(c) != std::string::npos);
            });
            sum += isupper(*badge) ? (int)*badge - 65 + 27 : (int)*badge - 96;
        }        
        std::cout << sum << std::endl;
    } 
    //auto t2 = std::chrono::high_resolution_clock::now();
    //auto us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    //std:: cout << "Executed in " << us.count() << " µs" << std::endl;
    return 0;
}
