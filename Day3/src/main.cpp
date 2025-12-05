#include <iostream>
#include <numeric>
#include <vector>
/*
void taskOne(){
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
}


int main(){
    taskOne();
    return 0;
}
*/

std::string maxJoltage(const std::string &bank, int n) {
  int k = bank.size();
  int toRemove = k - n; // how many digits we are allowed to discard
  std::vector<char> st; // acts like a stack
  st.reserve(k);

  for (char c : bank) {
    // Remove smaller digits when possible
    while (!st.empty() && toRemove > 0 && st.back() < c) {
      st.pop_back();
      toRemove--;
    }
    st.push_back(c);
  }

  // If still need to remove digits, remove from end
  while (toRemove > 0) {
    st.pop_back();
    toRemove--;
  }

  // Build result string of exactly n digits
  return std::string(st.begin(), st.begin() + n);
}

int main() {
  int n = 12;
  std::string line;
  std::vector<long long> joltage;
  while (std::getline(std::cin, line)) {
    joltage.push_back(std::stoll(maxJoltage(line, n)));
  }
  std::cout << std::accumulate(joltage.begin(), joltage.end(), 0LL) << '\n';
  return 0;
}