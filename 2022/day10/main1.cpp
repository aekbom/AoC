#include <fstream>
#include <vector>
#include <iostream>
#include <numeric>



inline void addSignalStrength(std::vector<int>& signalStrengths, int xReg, int cycleCount) {
    if ((cycleCount - 20) % 40 == 0) signalStrengths.push_back(cycleCount*xReg);    
} 

int main(int argc, char* argv[]) {
    std::ifstream inFile("./data.txt");       
    std::vector<int> signalStrengths;

    if (inFile.is_open()) {    
        std::string instruction;
        int cycleCount, steps = 0;
        int xReg = 1;                             
        while (!inFile.eof()) {
            inFile >> instruction;
            if (instruction == "addx") {
                inFile >> steps;
                cycleCount++;
                addSignalStrength(signalStrengths, xReg, cycleCount);            
                cycleCount++;                
                addSignalStrength(signalStrengths, xReg, cycleCount);
                xReg += steps;
            } else if (instruction == "noop") {
                cycleCount++;                
                addSignalStrength(signalStrengths, xReg, cycleCount);
            }
            if (cycleCount >= 220) break;    
        }         
        std::cout << std::accumulate(begin(signalStrengths), end(signalStrengths), 0) << std::endl;                                           
    }
    return 0;
} 
    
