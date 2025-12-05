#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class forkliftSheet {
private:
  int numCol, numRow, accRolls = 0;
  std::vector<char> sheet;

public:
  forkliftSheet();
  ~forkliftSheet() {}
  void readLine(std::string);
  int numberOfPaperRolls(int, int) const;
  void markAccessableRolls();
  int getAccRolls() const;

  void removeAccRolls();

  friend std::ostream &operator<<(std::ostream &, const forkliftSheet &);
};

forkliftSheet::forkliftSheet() {
  std::string line;
  std::getline(std::cin, line);
  numCol = line.size();
  readLine(line);
  while (std::getline(std::cin, line)) {
    readLine(line);
  }
  numRow = sheet.size() / numCol;
}

void forkliftSheet::readLine(std::string line) {
  while (line.size() < (size_t)numCol)
    line += ' ';
  for (int i = 0; i < numCol; i++) {
    sheet.push_back(line[i]);
  }
}

int forkliftSheet::numberOfPaperRolls(int i,
                                      int j) const { // base pos is j*numCol+i
  if (sheet.at(j * numCol + i) == '.')
    return 9;

  int accCnt = 0;

  // Directions: (dy, dx)
  static const int dirs[8][2] = {
      {-1, 0},  // up
      {0, 1},   // right
      {1, 0},   // down
      {0, -1},  // left
      {-1, -1}, // up-left
      {-1, 1},  // up-right
      {1, -1},  // down-left
      {1, 1}    // down-right
  };

  for (auto &d : dirs) {
    int ny = j + d[0];
    int nx = i + d[1];

    if (ny < 0 || ny >= numRow)
      continue;
    if (nx < 0 || nx >= numCol)
      continue;

    char c = sheet.at(ny * numCol + nx);
    if (c == 'x' || c == '@')
      accCnt++;
  }

  return accCnt;
}

void forkliftSheet::markAccessableRolls() {
  for (int i = 0; i < numCol; i++) {
    for (int j = 0; j < numRow; j++) {
      int nPaper = numberOfPaperRolls(i, j);
      if (nPaper < 4) {
        sheet.at(j * numCol + i) = 'x';
        accRolls++;
      }
    }
  }
}

int forkliftSheet::getAccRolls() const { return accRolls; }

void forkliftSheet::removeAccRolls() {
  std::for_each(this->sheet.begin(), this->sheet.end(),
                [](char &c) { c = (c == 'x' ? '.' : c); });
  accRolls = 0;
}

std::ostream &operator<<(std::ostream &os, const forkliftSheet &flS) {
  for (int j = 0; j < flS.numRow; j++) {
    for (int i = 0; i < flS.numCol; i++) {
      os << flS.sheet[j * flS.numCol + i] << ' ';
    }
    os << std::endl;
  }
  return os;
}

int main() {
  forkliftSheet *flS = new forkliftSheet();
  int sum = 0;

  flS->markAccessableRolls();
  std::cout << *flS << std::endl;
  // flS->removeAccRolls();
  // std::cout << *flS;
  while (flS->getAccRolls() > 0) {
    sum += flS->getAccRolls();
    std::cout << *flS;
    flS->removeAccRolls();
    flS->markAccessableRolls();
  }
  std::cout << sum << std::endl;
  delete flS;
  return 0;
}