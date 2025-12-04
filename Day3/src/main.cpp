#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main(){
    std::string line;
    std::vector<int> joltage;
    while(std::getline(std::cin, line)){  
        //find biggest digit up to n-1
        int indexA = 0, indexB = 0;
        for(int i = 0; i < line.size()-1; i++){
            if(int(line[i]) > int(line[indexA])){
                indexA = i;
            }
        }
        indexB = indexA+1;
        for(int i = indexA+1; i < line.size(); i++){
            if(int(line[i]) > int(line[indexB])){
                indexB = i;
            }
        }
        //std::string twoDigitLine = line[indexA]+line[indexB];
        int numberA = line[indexA]-48;
        int numberB = line[indexB]-48;
        int twoDigit = numberA*10+numberB;
        joltage.push_back(twoDigit);
    }
    for(auto it = joltage.begin(); it != joltage.end(); it++){
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "accumulate:\n";
    std::cout << std::accumulate( joltage.begin(), joltage.end(), 0 ) << '\n';
    return 0;
}