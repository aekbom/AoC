#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>




int main(int argc, char* argv[]) {       
    const uint32_t cLookAhead = 14; // 4 for solution 1, 14 for solution 2.
    std::ifstream inFile("./data.txt");
    std::string data;
        
    if (inFile.is_open()) {
        inFile >> data;
        uint32_t n = 0;
        for (auto i = begin(data); i < end(data); ++i) {            
            std::set tempSet(i, i+cLookAhead);
            if (tempSet.size() == cLookAhead) break;
            n++;          
        }
        std::cout << n+cLookAhead << std::endl;
    }
    return 0;
} 
    
