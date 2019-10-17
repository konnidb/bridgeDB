LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
		 -lgrpc++_reflection -lcrypto  \
		# -ldl

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

SRC_DIR := .
OBJ_DIR := build
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

all: client server

client: network.pb.o network.grpc.pb.o client.o auth/AuthService.o
	$(CXX) $^ $(LDFLAGS) -o build/$@.out

server: network.pb.o network.grpc.pb.o server.o auth/AuthService.o ServiceImplementation.o
	$(CXX) $^ $(LDFLAGS) -o build/$@.out

%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	protoc --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h client.out server.out