#include <iostream>
#include <string>
#include "network.grpc.pb.h"
#include "network.pb.h"
#include <grpc++/grpc++.h>
#include "ServiceImplementation.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using network::QueryService;
using network::QueryResponse;
using network::Query;
using network::CreateEdgeReq;
using network::CreateNodeReq;
using network::CreateEdgeResponse;
using network::CreateNodeResponse;
using network::NetworkNode;
using network::NetworkEdge;
using network::SearchNodeReq;
using network::SearchNodeResponse;

void Run()
{
    std::string address("0.0.0.0:5000");
    ServiceImplementation service;
    
    ServerBuilder builder;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;
    server->Wait();
};

int main()
{
    Run();
    return 0;
}