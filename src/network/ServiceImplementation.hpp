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

using network::CreateEdgeReq;
using network::CreateEdgeResponse;
using network::CreateNodeReq;
using network::CreateNodeResponse;
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

class ServiceImplementation final : public QueryService::Service
{
private:
public:
    Status CreateSession(
        ServerContext *context,
        const SessionRequest *request,
        Session *response) override;
    Status ExecuteQuery(
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
};