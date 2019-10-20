SRC_DIR := .
OBJ_DIR := build
SRC_FILES := $(wildcard */*.cpp)
STR_FILES := $(wildcard structs/*.cpp)
UTILS_FILES := $(wildcard utils/*.cpp)
OPERATIONS_FILES := $(wildcard operations/*.cpp)
CXXFLAGS = -Wall
CXXFLAGS += -I ../../
CXXFLAGS += -std=c++17

GRAPH_OJBS := $(wildcard ./../graph/*.o)
UTILS_OBJS := $(wildcard ./../utils/*.o)
ADMIN_OBJS := $(wildcard ./../admin/*.o)
all:
	# g++ -p build/ $(SRC_FILES)
	g++ $(CXXFLAGS) -c $(STR_FILES) $(UTILS_FILES) $(OPERATIONS_FILES) $(GRAPH_OJBS) $(UTILS_OBJS) $(ADMIN_OBJS)
structs:
	g++ $(CXXFLAGS) -o build/structs.o
clean:
	rm -rf *.o