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
using network::CreateEdgeReq;
using network::CreateNodeReq;
using network::CreateEdgeResponse;
using network::CreateNodeResponse;
using network::NetworkNode;
using network::NetworkEdge;
using network::SearchNodeReq;
using network::SearchNodeResponse;

class ServiceImplementation final: public QueryService::Service {
public:
    Status ExecuteQuery(
        ServerContext* context,
        const Query* query,
        QueryResponse* response
    ) override {
        response->set_response("HEllo world");
        return Status::OK;
    };
    Status CreateNode(
        ServerContext* context,
        const CreateNodeReq* req,
        CreateNodeResponse* response
    ) override {
        auto fields = req->fields();
        NetworkNode* node = response->mutable_node();
        (*node->mutable_fields())["field"] = fields["field"];
        return Status::OK;
    }

    Status CreateEdge(
        ServerContext* contest,
        const CreateEdgeReq* req,
        CreateEdgeResponse* response
    ) override {

        return Status::OK;
    }

    Status SearchNode(
        ServerContext* context,
        const SearchNodeReq* req,
        SearchNodeResponse* resp
    ) override {
        return Status::OK;
    }
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