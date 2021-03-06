LDFLAGS = -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
		 -lgrpc++_reflection -lcrypto  \
		# -ldl

CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++17
CXXFLAGS += -I ../../

GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

GRAPH_OJBS := $(wildcard ./../graph/structs.o)
UTILS_OBJS := $(wildcard ./../utils/*.o)
ADMIN_OBJS := $(wildcard ./../admin/*.o)

all: server

client: network.pb.o network.grpc.pb.o client.o auth/AuthService.o
	echo $(GRAPH_OJBS)
	$(CXX) $^ $(LDFLAGS) -o build/$@.out

server: network.pb.o network.grpc.pb.o server.o auth/AuthService.o ServiceImplementation.o graph/GraphToGrpc.o graph/GrpcToGraph.o graph/DBHandler.o
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o build/$@.out $(wildcard ./../graph/*.o) $(wildcard ./../admin/*.o) $(wildcard ./../utils/*.o)
	# ../graph/structs.o ../graph/Node.o ../graph/Edge.o ../graph/utils.o ../graph/Serializable.o ../graph/Database.o ../graph/Graph.o
	#$(UTILS_OBJS) $(ADMIN_OBJS)

%.grpc.pb.cc: %.proto
	protoc --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: %.proto
	protoc --cpp_out=. $<

clean:
	rm -f */*.o *.pb.cc *.pb.h client.out build/server.out