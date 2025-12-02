CXXFLAGS = -std=c++20 -Wall -Wpedantic -Wextra -g -O0

BIN=./bin/
SOURCE=./src/

.PHONY: all main clean

all: main

main: $(BIN)main


clean:
	rm -f $(BIN)*

$(BIN)main: $(SOURCE)main.cpp
	$(CXX) $(CXXFLAGS) -o $(BIN)main $(SOURCE)main.cpp

