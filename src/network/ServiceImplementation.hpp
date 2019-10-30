#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "network.grpc.pb.h"
#include "network.pb.h"
#include "auth/AuthService.hpp"
#include <grpc++/grpc++.h>
#include "src/graph/operations/Manipulation.h"
#include "src/graph/structs/Database.h"
#include "src/graph/structs/Graph.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using network::CreateEdgeReq;
using network::CreateEdgeResponse;
using network::CreateNodeReq;
using network::CreateNodeResponse;
using network::CreateRelationReq;
using network::CreateRelationResponse;
using network::DeleteEdgeReq;
using network::DeleteNodeReq;
using network::DeleteNodeResponse;
using network::GetPatternRequest;
using network::GetPatternResponse;
using network::NetworkEdge;
using network::NetworkNode;
using network::PatternEdge;
using network::PatternNode;
using network::Query;
using network::QueryResponse;
using network::QueryService;
using network::SearchNodeReq;
using network::SearchNodeResponse;
using network::Session;
using network::SessionRequest;
using network::SpanTreeReq;
using network::SpanTreeResponse;
using network::DeleteEdgeResponse;
using network::NetworkGraphRequest;
using network::NetworkGraphResponse;

class ServiceImplementation final : public QueryService::Service
{
public:
    Status GetGraph(
        ServerContext*, 
        const NetworkGraphRequest*,
        NetworkGraphResponse*
    ) override;
    Status CreateSession(
        ServerContext *context,
        const SessionRequest *request,
        Session *response) override;
    Status ConfigNewDB(
        ServerContext *context,
        const Query *query,
        QueryResponse *response) override;
    Status CreateNode(
        ServerContext *context,
        const CreateNodeReq *req,
        CreateNodeResponse *response) override;
    Status CreateEdge(
        ServerContext *contest,
        const CreateEdgeReq *req,
        CreateEdgeResponse *response) override;
    Status SearchNode(
        ServerContext *context,
        const SearchNodeReq *req,
        SearchNodeResponse *resp) override;
    Status GetPattern(
        ServerContext *ctx,
        const GetPatternRequest *req,
        GetPatternResponse *response) override;
    Status SpanTree(
        ServerContext *ctx,
        const SpanTreeReq *req,
        SpanTreeResponse *response) override;
    Status CreateRelation(
        ServerContext* ctx,
        const CreateRelationReq* req,
        CreateRelationResponse* response) override;
    Status DeleteNode(
        ServerContext *ctx,
        const DeleteNodeReq *req,
        DeleteNodeResponse *resp) override;
    Status DeleteEdge(
        ServerContext* ctx,
        const DeleteEdgeReq* req,
        DeleteEdgeResponse* resp
    ) override;
    ServiceImplementation();
    ~ServiceImplementation();
};
