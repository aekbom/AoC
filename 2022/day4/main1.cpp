#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <chrono>


int main(int argc, char* argv[]) {   
    //auto t1 = std::chrono::high_resolution_clock::now();
    std::ifstream inFile("./data.txt");
    uint32_t sum{0};
    if (inFile.is_open()) {
        for (std::string line; std::getline(inFile, line);) {
            line = line.substr(0, line.find('\r'));
            std::replace(line.begin(), line.end(), '-', ' ');
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream ss(line);
            std::vector<uint32_t> pair;        
            for (uint32_t num; ss >> num;) pair.push_back(num);
            std::vector<uint32_t> range1;
            std::vector<uint32_t> range2;
            for (auto i = pair[0]; i <= pair[1]; ++i) range1.push_back(i);
            for (auto i = pair[2]; i <= pair[3]; ++i) range2.push_back(i);
            
            // Solution 1
            //if (std::includes(range1.begin(), range1.end(), range2.begin(), range2.end()) ||
            //    std::includes(range2.begin(), range2.end(), range1.begin(), range1.end())) sum++;

            // Solution 2
            std::vector<uint32_t> overlap;
            std::set_intersection(range1.begin(), range1.end(), range2.begin(), range2.end(), 
                                  std::back_inserter(overlap));
            if (!overlap.empty()) sum++;            
        }
    }
    std::cout << sum << std::endl; 
    //auto t2 = std::chrono::high_resolution_clock::now();
    //auto us = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    //std:: cout << "Executed in " << us.count() << " µs" << std::endl;
    return 0;
}
