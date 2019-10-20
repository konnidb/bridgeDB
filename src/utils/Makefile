CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -I ../../
CXXFLAGS += -std=c++17
FILES = $(wildcard *.cpp)
all: Enums.o
	$(CXX) $^ -o utils.o

*.o:
	$(CXX) $(CXXFLAGS) -c %.cpp