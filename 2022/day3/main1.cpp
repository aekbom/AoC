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
        std::for_each(rucksacks.begin(), rucksacks.end(), [&](std::string& s) {
            sum += [](std::string compartment1, std::string compartment2) -> uint32_t {
                for (auto it = compartment1.begin(); it != compartment1.end(); ++it) {
                    if (compartment2.find(*it) != std::string::npos) 
                        return isupper(*it) ? (int)*it - 65 + 27 : (int)*it - 96;
                }
                return 0;   
            }(s.substr(0, s.length()/2), s.substr(s.length()/2));
        });                
        std::cout << sum << std::endl;
    } 
    //auto t2 = std::chrono::high_resolution_clock::now();
    //auto us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    //std:: cout << "Executed in " << us.count() << " µs" << std::endl;
    return 0;
}
