#ifndef UTIL_H
#define UTIL_H

class Point {
    public:
        int x;
        int y;
        Point() {}
        Point(int x, int y) : x{x}, y{y} {}
        Point operator+(Point p) { return Point(p.x + x, p.y + y); }      
        bool operator==(const Point& otherPoint) const { return (this->x == otherPoint.x && this->y == otherPoint.y); }
        struct HashFunction { 
            size_t operator()(const Point& point) const { 
                return std::hash<int>()(point.x) ^ (std::hash<int>()(point.y) << 1); 
            }
        };
};

std::ostream &operator<<(std::ostream &os, Point const &p) { 
    return os << '(' << p.x << ", " << p.y << ')';
}

inline bool notDigitOrSpace(char ch) {
    return ('0' <= ch && ch <= '9') or ch == ' ' or ch == '-';
}

std::string removeIrrelevantStuff(const std::string& input) {
    std::string result;
    std::copy_if(input.begin(), input.end(),
        std::back_inserter(result),
        notDigitOrSpace);
    return result;
}

#endif