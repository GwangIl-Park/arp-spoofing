CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRC_DIR = src
OBJ_DIR = obj
LIBS_DIR = $(SRC_DIR)/libs
UTILS_DIR = $(SRC_DIR)/utils

LIBS_SRC = $(wildcard $(LIBS_DIR)/*.cpp)
LIBS_HDR = $(wildcard $(LIBS_DIR)/*.h)
UTILS_SRC = $(wildcard $(UTILS_DIR)/*.cpp)
UTILS_HDR = $(wildcard $(UTILS_DIR)/*.h)
MAIN_SRC = $(SRC_DIR)/main.cpp

LIBS_OBJ = $(LIBS_SRC:$(LIBS_DIR)/%.cpp=$(OBJ_DIR)/%.o)
UTILS_OBJ = $(UTILS_SRC:$(UTILS_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_OBJ = $(MAIN_SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: arp_spoof

arp_spoof: $(LIBS_OBJ) $(UTILS_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(shell mkdir -p $(OBJ_DIR))

$(OBJ_DIR)/%.o: $(LIBS_DIR)/%.cpp $(LIBS_HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.cpp $(UTILS_HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIBS_HDR) $(UTILS_HDR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(LIBS_OBJ) $(UTILS_OBJ) $(MAIN_OBJ) my_program
