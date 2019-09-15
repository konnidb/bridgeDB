#include <string>

#include <grpcpp/grpcpp.h>
#include "network.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using network::Network;
using network::Query;
using network::QueryResponse;
using network::Credentials;
using network::AuthResponse;

const std::string user = "ivan";
const std::string password = "123";
const std::string token = "success";

class NetworkImplementation final : public Network::Service {
    Status auth(
        ServerContext* context, 
        const Credentials* credentials, 
        AuthResponse* reply
    ) override {
        if(credentials->user() == user && credentials->password() == password){
            reply->set_token(token);
            return Status::OK;
        }else{
            reply->set_token("Unahutorized");
            return Status::OK;
        }
    } 
};

void Run() {
    std::string address("0.0.0.0:5000");
    NetworkImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}