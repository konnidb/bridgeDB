CXX = g++
CXXFLAGS += -std=c++11
CXXFLAGS += -I ../../
CXXFLAGS += -std=c++17
FILES = $(wildcard *.cpp)
all: Enums.o
	$(CXX) -c $(FILES)

*.o:
	$(CXX) $(CXXFLAGS) -c %.cpp