#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

bool isVisible(const std::vector<std::vector<char>>& trees, int x, int y) {
    char candidateTree = trees[x][y];
    bool visible = true;
    for (int xx = x-1; xx >= 0; --xx) if (candidateTree <= trees[xx][y]) { visible = false; break; }
    if (visible) return true;
    visible = true;
    for (int xx = x+1; xx < trees.size(); ++xx) if (candidateTree <= trees[xx][y]) { visible = false; break; }
    if (visible) return true;
    visible = true;
    for (int yy = y+1; yy < trees[x].size(); ++yy) if (candidateTree <= trees[x][yy]) { visible = false; break; }
    if (visible) return true;
    visible = true;
    for (int yy = y-1; yy >= 0; --yy) if (candidateTree <= trees[x][yy]) { visible = false; break; }
    return visible;
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");       
    std::vector<std::vector<char>> trees;
    uint32_t sum{0};        
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
            sum += trees.size()*2 + trees[0].size()*2 - 4;
            for (int x=1; x < trees.size()-1; ++x)
                for (int y=1; y < trees[x].size()-1; ++y) sum += isVisible(trees, x, y) ? 1 : 0;
                        
            std::cout << sum << std::endl;                                           
        }
    return 0;
} 
    
