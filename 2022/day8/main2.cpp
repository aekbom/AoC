#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

uint32_t scenicScore(const std::vector<std::vector<char>>& trees, int x, int y) {
    char candidateTree = trees[x][y];
    uint32_t score{0};
    uint32_t treeCnt{0};
    for (int xx = x-1; xx >= 0; --xx) { treeCnt++; if (candidateTree <= trees[xx][y]) break; }
    score = treeCnt;
    treeCnt = 0;    
    for (int xx = x+1; xx < trees.size(); ++xx) { treeCnt++; if (candidateTree <= trees[xx][y]) break; }
    score *= treeCnt;
    treeCnt = 0;
    for (int yy = y+1; yy < trees[x].size(); ++yy) { treeCnt++; if (candidateTree <= trees[x][yy]) break; }
    score *= treeCnt;
    treeCnt = 0;
    for (int yy = y-1; yy >= 0; --yy) { treeCnt++; if (candidateTree <= trees[x][yy]) break; }
    return score * treeCnt;    
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");       
    std::vector<std::vector<char>> trees;
    uint32_t highestScore{0};        
        if (inFile.is_open()) {                        
            for (std::string line; std::getline(inFile, line);) {
                line = line.substr(0, line.find('\r'));
                std::stringstream ss(line);
                char c;
                std::vector<char> row;                
                while (ss >> c) {
                    row.push_back(c);
                }
                trees.push_back(row);
            }
            
            for (int x=1; x < trees.size()-1; ++x)
                for (int y=1; y < trees[x].size()-1; ++y) 
                    highestScore = std::max(scenicScore(trees, x, y), highestScore);
                                                       
            std::cout << highestScore << std::endl;                                           
        }
    return 0;
} 
    
