#pragma once
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
using network::SessionRequest;
using network::Session;

class ServiceImplementation final: public QueryService::Service {
public:
    Status CreateSession(
        ServerContext* context,
        const SessionRequest* request,
        Session* response
    ) override {
        return Status::OK;
    };

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
