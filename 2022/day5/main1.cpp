#include <fstream>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

void parseStackRow(std::string& line, std::vector<std::deque<char>>& stacks) {
    std::replace(line.begin(), line.end(), '[', ' ');
    std::replace(line.begin(), line.end(), ']', ' ');
    std::istringstream ss(line);
    for (char c; ss >> c;) {
        uint32_t bucket = std::round(ss.tellg() / 4.0) - 1;    
        stacks[bucket].push_front(c);        
    }
}

void parseAndPerformOperation(std::string& line, std::vector<std::deque<char>>& stacks) {
    std::istringstream ss(line);
    std::string dummy;
    uint32_t count, from, to;
    ss >> dummy >> count >> dummy >> from >> dummy >> to; from--; to--;
    // Solution 1
    //for (int i = 0; i < count; ++i) { stacks[to].push_back(stacks[from].back()); stacks[from].pop_back(); }

    // Solution 2
    std::move(stacks[from].end() - count, stacks[from].end(), std::back_inserter(stacks[to]));
    stacks[from].erase(stacks[from].end() - count, stacks[from].end());    
}

int main(int argc, char* argv[]) {       
    std::ifstream inFile("./data.txt");
    std::vector<std::deque<char>> stacks;
    uint32_t sum{0};        
        if (inFile.is_open()) {
            for (std::string line; std::getline(inFile, line);) {
                line = line.substr(0, line.find('\r'));                
                if (stacks.size() == 0) stacks.resize(std::round(line.length()/4.0));
                if (line.find('[') != std::string::npos) parseStackRow(line, stacks);
                else if (line.rfind('m', 0) == 0) parseAndPerformOperation(line, stacks);            
            }                        
            for (auto &v : stacks) std::cout << v.back();
        }
    return 0;
} 
    
