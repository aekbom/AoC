#include <fstream>
#include <vector>
#include <deque>
#include <iostream>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <sstream>

class Monkey {
    public:
        friend Monkey parseMonkey(std::ifstream& file);

        void turn(std::vector<Monkey>& monkeys) {
            for (auto item : items) {
                inspected++;
                item = operation(item);
                item = static_cast<int>(std::floor(item/3.0));
                monkeys[throwNext(item)].items.push_back(item);
            }
            items.clear();
        }        
        uint32_t inspected = 0;
    private:
        std::deque<int> items;
        std::function<int(int)> operation;
        std::function<int(int)> throwNext;        
};

Monkey parseMonkey(std::ifstream& file) {
    Monkey m;
    std::string line;
    do std::getline(file, line); while (line.rfind("Monkey", 6) != 0);    
    
    int t; 
    std::getline(file, line);
    line.erase(begin(line), begin(line)+18);
    std::replace(begin(line), end(line), ',', ' ');        
    std::stringstream ss(line);                
    while (ss >> t) m.items.push_back(t);
    
    std::getline(file, line);
    line.erase(begin(line), begin(line)+23);   
    ss.clear(); ss.str(line);
    char op;
    ss >> op;
    bool self = true;
    if (ss >> t) self=false;
    m.operation = [op, t, self](int old) -> int {
        if (self) return op == '+' ? old + old : old * old; 
        else return op == '+' ? old + t : old * t; 
    };
    
    std::getline(file, line);        
    line.erase(begin(line), begin(line)+21);   
    ss.clear(); ss.str(line);
    int divisor;
    ss >> divisor;

    std::getline(file, line);        
    line.erase(begin(line), begin(line)+29);   
    ss.clear(); ss.str(line);
    int trueThrow;
    ss >> trueThrow;
    
    std::getline(file, line);        
    line.erase(begin(line), begin(line)+30);   
    ss.clear(); ss.str(line);
    int falseThrow;
    ss >> falseThrow;
    m.throwNext = [trueThrow, falseThrow, divisor](int worryLevel) -> int {
        return (worryLevel % divisor == 0) ? trueThrow : falseThrow;
    };        
    
    return m;
}

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");     
    std::vector<Monkey> monkeys;

    if (inFile.is_open()) {    
        while (!inFile.eof()) monkeys.push_back(parseMonkey(inFile));
        for (int round=1; round<=20; ++round) {
            for (int i=0; i<monkeys.size(); ++i) monkeys[i].turn(monkeys);
        }      
        std::sort(begin(monkeys), end(monkeys), [](Monkey a, Monkey b) {
            return a.inspected > b.inspected;
        });        
        std::cout << monkeys[0].inspected*monkeys[1].inspected << std::endl;
    }
    return 0;
} 
    
