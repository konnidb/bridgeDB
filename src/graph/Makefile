SRC_DIR := .
OBJ_DIR := build
SRC_FILES := $(wildcard */*.cpp)
STR_FILES := $(wildcard structs/*.cpp)
CXXFLAGS = -Wall
all:
	# g++ -p build/ $(SRC_FILES)
	echo $(STR_FILES)
	g++ -I ../../ -Wall -c $(STR_FILES)	
structs:
	g++ -Wall -o build/structs.o 
clean:
	rm -rf *.o