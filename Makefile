CXX = g++  
CXXFLAGS = -Wall -std=c++11 

SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
BIN_DIR = bin
TESTS_DIR = tests

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

test: $(TESTS_DIR)/testes
	$(TESTS_DIR)/testes

$(TESTS_DIR)/testes: $(OBJ_FILES) $(TESTS_DIR)/testes.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TESTS_DIR)/testes.o: $(TESTS_DIR)/testes.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/* $(TESTS_DIR)/*.o $(TESTS_DIR)/testes

.PHONY: all test clean
