#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>


typedef std::pair<int, int> point;
constexpr int width = 1024;
constexpr int height = 256;

enum matter : char {
    air = 0,
    rock = 1,
    sand = 2
};

std::size_t replaceAll(std::string& inout, std::string_view what, std::string_view with) {
    std::size_t count{};
    for (std::string::size_type pos{};
         inout.npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
    return count;
}

void drawLine(point from, point to, std::array<std::array<char, height>, width>& cave) {
    if (from.first == to.first) {
        int inc = from.second < to.second ? 1 : -1;
        for (int i=from.second; i!=to.second; i += inc) { cave[from.first][i] = matter::rock; }
    } else {
        int inc = from.first < to.first ? 1 : -1;
        for (int i=from.first; i!=to.first; i += inc) { cave[i][from.second] = matter::rock; }
    }
    cave[to.first][to.second] = matter::rock;
}

bool dropSand(std::array<std::array<char, height>, width>& cave) {
    if (cave[500][0] != matter::air) return false;
    for (int y=0, lastY=-1, x=500; y < height and y>lastY; ++y) {
        if (cave[x][y] != matter::air) {
            if (cave[x-1][y] != matter::air)
                if (cave[x+1][y] != matter::air) { cave[x][lastY] = matter::sand; return true; }
                else x++;
            else x--;
        }
        lastY = y;
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");
    std::array<char, height> row;
    row.fill(matter::air);
    std::array<std::array<char, height>, width> cave;
    cave.fill(row);
    int largestY = 0;
    if (inFile.is_open()) {
        // Parsing input.                              
        for (std::string line; std::getline(inFile, line);) { 
            bool first = true;
            point last; 
            line = line.substr(0, line.find('\r'));
            std::replace(begin(line), end(line), ',', ' ');
            replaceAll(line, "->", " ");
            std::stringstream ss(line);
            point p;
            while (ss >> p.first >> p.second) {
                if (p.second > largestY) largestY = p.second;
                if (!first) drawLine(last, p, cave);
                else first = false;
                last = p;
            }
        }
        // Comment in below line for assignment 2.
        // drawLine(point(0, largestY+2), point(width-1, largestY+2), cave);
        uint32_t sandCnt{0};
        while (dropSand(cave)) ++sandCnt;
        std::cout << sandCnt << std::endl;        
    }
    return 0;
} 
    