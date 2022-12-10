#include <fstream>
#include <set>
#include <iostream>
#include <algorithm>

typedef std::pair<int, int> point;
typedef point vector;

inline vector moveDir(char c) {
    switch (c) {
        case 'U' : return vector(0, -1);
        case 'D' : return vector(0, 1);
        case 'L' : return vector(-1, 0);
        case 'R' : return vector(1, 0);
    }
    return vector(0, 0);
}

inline vector tailMove(const point& head, const point& tail) {
    int xDiff = head.first - tail.first;
    int yDiff = head.second - tail.second;    

    if (std::abs(xDiff) > 1 or std::abs(yDiff) > 1) { // Tail needs to move.        
        return vector(std::clamp(xDiff, -1, 1), std::clamp(yDiff, -1, 1));
    }
    return vector(0, 0);       
}

void performSteps(vector dir, int count, std::set<point>& visited) {
    static std::vector<point> rope(10, {0,0});
    
    for (int i=0; i<count; ++i) {
        auto head = begin(rope);
        *head = point(head->first+dir.first, head->second+dir.second);
        std::vector<point>::iterator tail;
        for (; head < end(rope)-1; ++head) {            
            tail = head+1;
            vector move = tailMove(*head, *tail);
            *tail = point(tail->first + move.first, tail->second + move.second);
        }
        visited.insert(*tail);
    }
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");       
    std::set<point> visited;    
    if (inFile.is_open()) {    
        char dir;
        int steps;                             
        while (!inFile.eof()) {
            inFile >> dir >> steps;
            performSteps(moveDir(dir), steps, visited);
        }                                 
        std::cout << visited.size() << std::endl;                                           
    }
    return 0;
} 