#include <iostream>
#include <string>
#include "network.grpc.pb.h"
#include "network.pb.h"
#include "auth/AuthService.hpp"
#include <grpc++/grpc++.h>
#include "ServiceImplementation.hpp"
#include "graph/GraphToGrpc.h"
#include "src/graph/structs/Node.h"
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
using network::NetworkGraphRequest;
using network::NetworkGraphResponse;
using network::NetworkNode;
using network::NtEdgeArr;
using network::NtNodeArr;
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

Status ServiceImplementation::CreateSession(
    ServerContext *context,
    const SessionRequest *request,
    Session *response)
{
    string username = request->username();
    string password = request->password();
    string database = request->database();
    cout << username << endl;
    // if (AuthService::validate_credentials(username, password)) {
    //     return Status::CANCELLED;
    // }
    string token = AuthService::generate_token(username, database).c_str();
    string* tkn = response->mutable_token();
    *tkn = token;
    return Status::OK;
};

Status ServiceImplementation::ExecuteQuery(
    ServerContext *context,
    const Query *query,
    QueryResponse *response)
{
    response->set_response("HEllo world");
    return Status::OK;
};
Status ServiceImplementation::CreateNode(
    ServerContext *context,
    const CreateNodeReq *req,
    CreateNodeResponse *response)
{
    auto fields = req->fields();
    Node* n = new Node();
    n->properties["field1"] = "Prop1";
    NetworkNode *node = response->mutable_node();
    GraphToGrpc::parse_node(n, node);
    (*node->mutable_fields())["field"] = "ASDASDAsd";
    return Status::OK;
}

Status ServiceImplementation::CreateEdge(
    ServerContext *contest,
    const CreateEdgeReq *req,
    CreateEdgeResponse *response)
{

    return Status::OK;
}

Status ServiceImplementation::SearchNode(
    ServerContext *context,
    const SearchNodeReq *req,
    SearchNodeResponse *resp)
{
    return Status::OK;
}

Status ServiceImplementation::GetPattern(
    ServerContext *context,
    const GetPatternRequest *req,
    GetPatternResponse *resp)
{
    return Status::OK;
}

Status ServiceImplementation::SpanTree(
    ServerContext *ctx,
    const SpanTreeReq *req,
    SpanTreeResponse *response)
{

    return Status::OK;
}