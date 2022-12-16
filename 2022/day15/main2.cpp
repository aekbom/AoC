#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "util.h"

int findGapInRanges(std::vector<std::pair<int, int>>& ranges) {
    std::sort(begin(ranges), end(ranges), [](std::pair<int, int> a, std::pair<int, int> b){
        return a < b;
    });

    int endOfRange = ranges[0].second;
    for (auto p : ranges) {
        if (p.first-1 > endOfRange) return p.first-1;
        endOfRange = std::max(endOfRange, p.second);
    }
    return -1;
}

Point missingPoint(std::vector<std::pair<Point, Point>>& sb) {
    const int dimE = 4000000;
    const int dimS = 0;
    std::vector<std::pair<int, int>> ranges;
    for (int y=dimS; y<=dimE; ++y) {
        int start = dimE;
        int end = dimS;
        for (auto p : sb) {
            int dist = std::abs(p.first.x - p.second.x) + std::abs(p.first.y - p.second.y);
            if ((p.first.y <= y and p.first.y + dist >= y) or (p.first.y-dist <= y and p.first.y >= y)) {
                dist = dist - std::abs(y - p.first.y);
                auto s = std::clamp(p.first.x - dist, dimS, dimE);
                auto e = std::clamp(p.first.x + dist, dimS, dimE);
                start = start > s ? s : start;
                end = end < e ? e : end;
                ranges.push_back(std::make_pair(s, e));
            } 
        }
        if (int x = findGapInRanges(ranges); x >= 0) return Point(x, y);
        ranges.clear(); 
    }
    return Point(0, 0);
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");
    std::vector<std::pair<Point, Point>> sensorAndBeacons;
    if (inFile.is_open()) {
        // Parsing input.                              
        for (std::string line; std::getline(inFile, line);) { 
            line = removeIrrelevantStuff(line);
            std::stringstream ss(line);
            Point s, b;
            while (ss >> s.x >> s.y >> b.x >> b.y) sensorAndBeacons.push_back(std::make_pair(s,b));
        }
        auto point = missingPoint(sensorAndBeacons);
        auto tuningFrequency = (int64_t)point.x*(int64_t)4000000 + point.y;
        std::cout << tuningFrequency << std::endl;
    }
    return 0;
} 
    