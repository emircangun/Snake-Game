CC := g++
CXXFLAGS := -Wall -Werror -std=c++17
SRC := ./src/*.cpp
EXE := main

$(EXE): $(EXE).cpp
	$(CC) $(CXXFLAGS) $(EXE).cpp $(SRC) -o $(EXE)
