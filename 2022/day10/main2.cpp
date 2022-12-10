#include <fstream>
#include <vector>
#include <iostream>
#include <numeric>


inline void printCycle(int cycle, int regX) {
    int c = (cycle-1) % 40;
    std::cout << (std::abs(c-regX) > 1 ? "." : "#");
    if (cycle % 40 == 0) std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");           
    if (inFile.is_open()) {    
        std::string instruction;
        int cycle = 0, arg = 0;
        int xReg = 1;                            
        while (!inFile.eof()) {
            inFile >> instruction;            
            if (instruction == "addx") {
                inFile >> arg;
                cycle++;                
                printCycle(cycle, xReg); 
                cycle++;
                printCycle(cycle, xReg);                 
                xReg += arg;
            } else if (instruction == "noop") {
                cycle++;
                printCycle(cycle, xReg);
            }
        }         
    }
    return 0;
} 
    
