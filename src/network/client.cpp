#include <string>

#include <grpc++/grpc++.h>
#include "network.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using network::QueryService;
using network::Query;
using network::QueryResponse;
using network::NetworkNode;
using network::CreateNodeReq;
using network::CreateNodeResponse;

class NetworkClient {
    public:
        NetworkClient(std::shared_ptr<Channel> channel) : stub_(QueryService::NewStub(channel)) {}

    std::string sendRequest(std::string a) {
        NetworkNode* node = new NetworkNode();
        CreateNodeReq req;
        req.set_id(12);
        auto fields = req.mutable_fields();
        (*fields)["field"] = a;

        // request.set_user(user);
        // request.set_password(password);

        CreateNodeResponse reply;

        ClientContext context;

        Status status = stub_->CreateNode(&context, req, &reply);

        if(status.ok()){
            return reply.node().fields().at("field");
        } else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return reply.node().fields().at("field");            
        }
    }

    private:
        std::unique_ptr<QueryService::Stub> stub_;
};

void Run() {
    std::string address("0.0.0.0:5000");
    NetworkClient client(
        grpc::CreateChannel(
            address, 
            grpc::InsecureChannelCredentials()
        )
    );

    std::string response;
    std::string a = "";
    std::cin >> a;

    response = client.sendRequest(a);
    std::cout << response << std::endl;
}

int main(int argc, char* argv[]){
    Run();

    return 0;
}