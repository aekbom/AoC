#include <fstream>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

std::string getKey(const std::deque<std::string>& currentDir, 
                   const std::deque<std::string>::iterator endAt) {
    std::string key;
    for (auto it = begin(currentDir); it < endAt; ++it) {
        key = key + *it;
    }
    return key;
}

int main(int argc, char* argv[]) {       
    std::ifstream inFile("./data.txt");
    std::map<std::string, uint32_t> directorySizes;
    std::deque<std::string> currentDir;

    uint32_t sum{0};        
    if (inFile.is_open()) {
        for (std::string line; std::getline(inFile, line);) {
            if (line.rfind('$', 0) == 0) {
                std::istringstream ss(line);
                std::string dummy, cmd, arg;
                ss >> dummy >> cmd;
                if (cmd == "cd") { 
                    ss >> arg;
                    if (arg == "..") {                            
                        currentDir.pop_back();                             
                    } else {                            
                        currentDir.push_back(arg);                            
                        directorySizes[getKey(currentDir, end(currentDir))] = 0;                            
                    }
                }
            } else {
                std::string dirOrSize, name;
                std::istringstream ss(line);
                ss >> dirOrSize >> name;                                        
                if (dirOrSize.find("dir") == std::string::npos) {
                    uint32_t fileSize = std::atoi(dirOrSize.c_str());
                    for (auto it = currentDir.begin()+1; it <= currentDir.end(); ++it) directorySizes[getKey(currentDir, it)] += fileSize;
                }                                                                                                  
            }
        }
        for (auto& [key, val] : directorySizes) if (val <= 100000) sum += val;                        
        std::cout << sum << std::endl;
    }
    return 0;
} 