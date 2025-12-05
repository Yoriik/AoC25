#include <iostream>
#include <string>

class elfSafe {
private:
  int value;
  int countedZeros;

public:
  elfSafe() : value{50}, countedZeros{0} {}
  bool turnDial();
  bool validateValueState(const int);
  void countRotation(int, int);
  int getCountedZeros() const { return countedZeros; }
  int getValue() const { return value; }
};

bool elfSafe::turnDial() {
  int delta, sum = 0, prevValue = 0;
  std::string line;
  while (std::getline(std::cin, line)) {

    if (line[0] == 'R') {
      delta = +1;
    } else {
      delta = -1;
    }

    line = line.substr(1, line.size());
    sum = std::stoi(line, nullptr, 10);
    prevValue = value;
    countRotation(delta, sum);
    value += delta * sum;
    value = value % 100;
    std::cout << "value after modulo " << value << std::endl;
    if (value < 0)
      value += 100;
    std::cout << value << std::endl;
    // if(!this->validateValueState(prevValue)){ std::cout << "ERROR" <<
    // std::endl; return false;}
  }
  return true;
}

void elfSafe::countRotation(int delta, int sum) {
  for (int i = 1; i <= sum; i++) {
    if ((value + (delta * i)) % 100 == 0 ||
        (value + (delta * i)) % 100 == 100) {
      countedZeros++;
    }
  }
}

bool elfSafe::validateValueState(const int prevValue) {
  int x = 0;
  if (value > 99) {
    // x = int(value/100);
    value = value - 100;
    x += 1;
    std::cout << "x in validate: " << x << std::endl;
    // value = value%100;
    // if(x < 0) x = -1*x;
    countedZeros += x;
    if (value > 99)
      validateValueState(prevValue);
  } else {
    if (value < 0) {
      // x = int(value/100);
      value = value + 100;
      if (prevValue != 0) {
        x += 1;
        std::cout << "x in validate: " << x << std::endl;
        // value = (value)%100;
        // if(x < 0) x = -1*x;
        countedZeros += x;
        if (value < 0)
          validateValueState(prevValue);
      }
    } else {
      if (value == 0) {
        countedZeros++;
      }
    }
  }
  return true;
}

int main() {
  elfSafe s;
  s.turnDial();
  std::cout << s.getValue() << std::endl;
  std::cout << s.getCountedZeros() << std::endl;
  return 0;
}