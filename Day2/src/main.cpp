#include <cstring>
#include <iostream>
#include <string>
#include <vector>

bool validateID(long unsigned int j) {
  std::string Id = std::to_string(j);
  if (Id[0] == '0')
    return false;
  int validCnt = 0;
  for (long unsigned int l = 0; l < Id.size() / 2; l++) {
    if (Id.size() % (l + 1) == 0) {
      int numberOfSubStr =
          Id.size() / (l + 1); // number of substrings of length l+1
      validCnt = 0;
      std::string a = Id.substr(0, l + 1);
      int m = a.size();

      const char *str = Id.c_str();
      const char *target = a.c_str();

      for (const char *result = str; (result = std::strstr(result, target));
           result += a.size()) {
        validCnt++;
      }
      if (validCnt == numberOfSubStr)
        return false;
    }
  }
  return true;
}

int main() {
  std::string line, ID1, ID2;
  std::getline(std::cin, line);
  long unsigned int indexA = 0, IdSum = 0;
  int listSize = 0;
  std::vector<std::string> IdList;

  for (long unsigned int i = 0; i < line.size(); i++) {
    if (line[i] == '-' || line[i] == ',') {
      IdList.push_back(line.substr(indexA, i));
      listSize++;
      indexA = i + 1;
    }
  }

  for (int i = 0; i < listSize / 2; i++) {
    ID1 = IdList[2 * i];
    ID2 = IdList[2 * i + 1];
    for (long unsigned int j = std::stoll(IdList[2 * i]);
         j <= std::stoll(IdList[2 * i + 1]); j++) {
      if (!validateID(j)) {
        IdSum += j;
      }
    }
  }
  std::cout << IdSum << std::endl;

  return 0;
}