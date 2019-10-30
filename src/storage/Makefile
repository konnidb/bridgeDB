CXX = g++
CXXFLAGS += -I ../../
CXXFLAGS += -std=c++17
UTILS_DIR = ../utils
FILES = $(wildcard *.cpp)
UTILS_OBJS = $(wildcard $(UTILS_DIR)/*.o)
all:
	$(CXX) $(CXXFLAGS) -c $(FILES) $(UTILS_OBJS)