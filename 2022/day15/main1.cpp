#include <fstream>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "util.h"

std::unordered_set<Point, Point::HashFunction> coveredArea(std::vector<std::pair<Point, Point>>& sb) {
    std::unordered_set<Point, Point::HashFunction> a;
    for (auto p : sb) {
        int dist = std::abs(p.first.x - p.second.x) + std::abs(p.first.y - p.second.y);
        const int y = 2000000;
        if ((p.first.y <= y and p.first.y + dist >= y) or (p.first.y-dist <= y and p.first.y >= y)) {
            dist = dist - std::abs(y - p.first.y);      
            for (int x=0; x <= dist; ++x) {
                Point pp;             
                pp.x = p.first.x + x; pp.y = y; a.insert(pp);                
                pp.x = p.first.x - x; pp.y = y; a.insert(pp);
            }   
        }    
    }
    return a;
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");
    std::vector<std::pair<Point, Point>> sensorAndBeacons;
    std::unordered_set<Point, Point::HashFunction> beacons;
    if (inFile.is_open()) {
        // Parsing input.                              
        for (std::string line; std::getline(inFile, line);) { 
            line = removeIrrelevantStuff(line);
            std::stringstream ss(line);
            Point s, b;
            while (ss >> s.x >> s.y >> b.x >> b.y) { 
                beacons.insert(b);               
                sensorAndBeacons.push_back(std::make_pair(s,b));
            }
        }
        auto set = coveredArea(sensorAndBeacons);
        uint32_t sum{0};
        for (auto a : set) if (beacons.find(a) == end(beacons)) sum++;
        std::cout << sum << std::endl;
    }
    return 0;
} 
    