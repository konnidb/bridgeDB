LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
		 -lgrpc++_reflection  \
		# -ldl

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

all: client server

client: network.pb.o network.grpc.pb.o client.o
	$(CXX) $^ $(LDFLAGS) -o $@.out

server: network.pb.o network.grpc.pb.o server.o
	$(CXX) $^ $(LDFLAGS) -o $@.out

%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	protoc --cpp_out=. $<

# clean:
# 	rm -f *.o *.pb.cc *.pb.h client server