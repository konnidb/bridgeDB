#pragma once
#include <iostream>
#include <string>
#include "network.grpc.pb.h"
#include "network.pb.h"
#include "auth/AuthService.hpp"
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

class ServiceImplementation final: public QueryService::Service
{
private:
    
public:
    Status CreateSession(
    ServerContext* context,
    const SessionRequest* request,
    Session* response
    ) override;
    Status ExecuteQuery(
    ServerContext* context,
    const Query* query,
    QueryResponse* response
    ) override;
    Status CreateNode(
    ServerContext* context,
    const CreateNodeReq* req,
    CreateNodeResponse* response
    ) override;
    Status CreateEdge(
    ServerContext* contest,
    const CreateEdgeReq* req,
    CreateEdgeResponse* response
    ) override;
    Status SearchNode(
    ServerContext* context,
    const SearchNodeReq* req,
    SearchNodeResponse* resp
    ) override;
};
