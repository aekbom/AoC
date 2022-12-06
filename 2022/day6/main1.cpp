#include <fstream>
#include <iostream>
#include <algorithm>
#include <set>


int main(int argc, char* argv[]) {       
    const uint32_t cLookAhead = 4;
    std::ifstream inFile("./data.txt");
    std::string data;
        
    if (inFile.is_open()) {
        inFile >> data;
        uint32_t n = 0;
        for (auto i = begin(data); i < end(data); ++i) {            
            std::set tempSet(i, i+cLookAhead);
            if (n > cLookAhead && tempSet.size() == cLookAhead) break;
            n++;          
        }
        std::cout << n+cLookAhead << std::endl;
    }
    return 0;
} 
    
