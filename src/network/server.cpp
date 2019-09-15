#include <iostream>
#include <string>
#include "network.grpc.pb.h"
#include "network.pb.h"
#include <grpc++/grpc++.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using network::QueryService;
using network::QueryResponse;
using network::Query;

class ServiceImplementation final: public QueryService::Service {
public:
    // ServiceImplementation(){};
    // ~ServiceImplementation(){};
    Status ExecuteQuery(
        ServerContext* context,
        const Query* query,
        QueryResponse* response
    ) override {
        response->set_response("HEllo world");
        return Status::OK;
    };
};

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