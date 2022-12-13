#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <unordered_set>
#include <set>

typedef std::pair<short, short> point;

class Node;

std::vector<std::vector<Node*>> nodes;
std::unordered_set<Node*> unvisited;
std::set<Node*> prio;

class Node {
    public:
        inline std::vector<Node*> neighbors() {
            return std::vector<Node*> {
                (pos.second > 0) ? nodes[pos.first][pos.second-1] : nullptr, 
                (pos.second < nodes[0].size()-1) ? nodes[pos.first][pos.second+1] : nullptr,
                (pos.first > 0) ? nodes[pos.first-1][pos.second] : nullptr,
                (pos.first < nodes.size()-1) ? nodes[pos.first+1][pos.second] : nullptr
            };
        }
        inline void evaluateNeighborScores() {
            for (auto neighbor : neighbors()) {
                if (neighbor and unvisited.find(neighbor) != unvisited.end()) {
                    neighbor->evaluateNewScore(this);
                    prio.insert(neighbor);
                }
            }
        }
        inline void evaluateNewScore(Node* f) { score = std::min(score, (c - f->c <= 1 ? f->score+1 : std::numeric_limits<uint32_t>::max())); }
        void print() { std::cout << " (" << pos.first << ", " << pos.second << ") -> " << score << std::endl; }
        point pos;
        uint32_t score;
        char c;
};

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");
    auto cmp = [](Node* left, Node* right) { return left->score < right->score; };     
    short lineCnt{0};
    constexpr bool firstPuzzle = true;
    Node* endNode = nullptr;
    if (inFile.is_open()) {
        // Parsing input.                                
        for (std::string line; std::getline(inFile, line); ++lineCnt) { 
            line = line.substr(0, line.find('\r'));
            std::vector<Node*> row;
            for (auto it = begin(line); it < end(line); ++it) {
                Node* n = new Node();
                n->pos = point(lineCnt, std::distance(begin(line), it));
                if (*it == 'S') {
                    n->score = firstPuzzle ? 0 : std::numeric_limits<uint32_t>::max();
                    n->c = firstPuzzle ? 'a' : 'z';
                    if (!firstPuzzle) endNode = n;
                    else prio.insert(n);
                } else if (*it == 'E') {
                    n->score = firstPuzzle ? std::numeric_limits<uint32_t>::max() : 0;
                    n->c = firstPuzzle ? 'z' : 'a';                                        
                    if (firstPuzzle) endNode = n;
                    else prio.insert(n);
                } else {
                    n->score = std::numeric_limits<uint32_t>::max();                                      
                    n->c = firstPuzzle ? *it : 'z' - *it + 'a';                    
                }  
                row.push_back(n);
                unvisited.insert(n);
            }
            nodes.push_back(row);
        }
        
        // Modified Dijkstra's
        while (!unvisited.empty()) { 
            auto it = std::min_element(begin(prio), end(prio), cmp);
            if ((*it)->score == std::numeric_limits<uint32_t>::max()) break;            
            if (unvisited.find(*it) != unvisited.end()) {                                     
                (*it)->evaluateNeighborScores();
                unvisited.erase(*it);
                prio.erase(it);                
            }
        }
        
        if (firstPuzzle) endNode->print();

        // Finding best node to start from and cleaning up.
        endNode = nullptr;
        uint32_t lowestScore = std::numeric_limits<uint32_t>::max();  
        for (auto v : nodes) {
            for (auto n : v) {
                if (n->c == 'z' and n->score < lowestScore) {
                    lowestScore = n->score;
                    if (endNode) delete endNode;
                    endNode = n;                    
                } else delete n;
            }
        }

        if (!firstPuzzle) endNode->print();
    }
    return 0;
} 
    
