CXXFLAGS = -std=c++20 -Wall -Wpedantic -Wextra -g -O0

BIN=./bin/
SOURCE=./src/

.PHONY: all main main2 clean

all: main main2

main: $(BIN)main 
main2: $(BIN)main2


clean:
	rm -f $(BIN)*

$(BIN)main: $(SOURCE)main.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)main $(SOURCE)main.cpp

$(BIN)main2: $(SOURCE)main2.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)main2 $(SOURCE)main2.cpp

