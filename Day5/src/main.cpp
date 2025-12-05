#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Expecting int as part of day." << std::endl;
    return -1;
  }
  if (*argv[1] == '1') {
    std::string line;
    std::vector<long unsigned int> IdList;

    while (std::getline(std::cin, line) && !line.empty()) {
      auto dash = line.find('-');
      IdList.push_back(std::stoll(line.substr(0, dash)));
      IdList.push_back(std::stoll(line.substr(dash + 1)));
    }

    bool fresh = false;
    std::vector<long unsigned int> freshNum;

    while (std::getline(std::cin, line)) {
      fresh = false;
      long unsigned int num = std::stoll(line);
      std::vector<long unsigned int>::iterator it = IdList.begin();
      while (it != IdList.end() && !fresh) {
        if (num >= *it && num <= *(it + 1)) {
          fresh = true;
          freshNum.push_back(num);
        }
        it++;
        it++;
      }
    }

    std::cout << std::endl << freshNum.size() << std::endl;
    return 0;
  }
  if (*argv[1] == '2') {
    std::vector<std::pair<long long, long long>> IdList;
    std::string line;

    while (std::getline(std::cin, line) && !line.empty()) {
      auto dash = line.find('-');
      long long a = std::stoll(line.substr(0, dash));
      long long b = std::stoll(line.substr(dash + 1));
      IdList.emplace_back(a, b);
    }

    std::sort(IdList.begin(), IdList.end());

    std::vector<std::pair<long long, long long>> merged;
    for (auto &ids : IdList) {
      if (merged.empty() || ids.first > merged.back().second + 1) {
        merged.push_back(ids);
      } else {
        merged.back().second = std::max(merged.back().second, ids.second);
      }
    }
    long long total = 0;
    for (auto &iv : merged) {
      total += (iv.second - iv.first + 1);
    }

    std::cout << total << std::endl;
    return 0;
  }
}