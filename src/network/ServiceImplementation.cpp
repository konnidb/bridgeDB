#include <iostream>
#include <string>
#include "network.grpc.pb.h"
#include "network.pb.h"
#include "auth/AuthService.hpp"
#include <grpc++/grpc++.h>
#include "ServiceImplementation.hpp"
#include "src/graph/structs/Edge.h"
#include "graph/GraphToGrpc.h"
#include "graph/GrpcToGraph.h"
#include "src/graph/structs/Node.h"
#include "src/graph/structs/Graph.h"
#include "src/graph/operations/Manipulation.h"
#include "src/graph/utils/Comparison.h"
#include "src/graph/structs/Database.h"
#include "./graph/DBHandler.h"
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
using network::CreateRelationReq;
using network::CreateRelationResponse;

Status ServiceImplementation::CreateSession(
    ServerContext *context,
    const SessionRequest *request,
    Session *response)
{
    string username = request->username();
    string password = request->password();
    string database = request->database();
    if (AuthService::validate_credentials(username, password)) {

        string token = AuthService::generate_token(username, database);
        string* tkn = response->mutable_token();
        AuthData data = AuthService::get_credentials(token);
        cout << token << " " << data.database_name << endl;
        *tkn = token;
        return Status::OK;
    }

    return Status::CANCELLED;
};

Status ServiceImplementation::ExecuteQuery(
    ServerContext *context,
    const Query *query,
    QueryResponse *response)
{
    string token = (string)query->token();
    cout<<token;
    DBHandler handler("dbperrona");
    handler.createConfigFile("dbperrona");
    response->set_response("HEllo world");
    return Status::OK;
};
Status ServiceImplementation::CreateNode(
    ServerContext *context,
    const CreateNodeReq *req,
    CreateNodeResponse *response)
{
    AuthData data = AuthService::get_credentials(req->token());
    
    cout << "CREATING NODE";
    Node* node = new Node();
    NetworkNode req_node = (NetworkNode)req->node();
    NetworkNode* res_node = response->mutable_node();
    GrpcToGraph::parse_node(&req_node, node);
    Node* stored_node = manipulations[data.database_name]->createNode(node->properties);
    GraphToGrpc::parse_node(stored_node, res_node);
    return Status::OK;
}

Status ServiceImplementation::CreateEdge(
    ServerContext *contest,
    const CreateEdgeReq *req,
    CreateEdgeResponse *response)
{
    
    AuthData data = AuthService::get_credentials(req->token());
    auto& manpl = manipulations[data.database_name];
    cout << "CREATING EDGE";
    NetworkEdge nt_req_edge = (NetworkEdge)req->edge();
    Edge* edge = new Edge();
    GrpcToGraph::parse_edge(&nt_req_edge, edge);
    NetworkNode nt_rq_or = (NetworkNode)nt_req_edge.origin();
    NetworkNode nt_rq_dst = (NetworkNode)nt_req_edge.destination();
    long origin_id = (long)(nt_rq_or.id());
    long dest_id = (long)(nt_rq_dst.id());
    Node* or_node = manpl->getNodeById(origin_id);
    Node* dest_node = manpl->getNodeById(dest_id);
    Edge* res_edge = manpl->createEdge(origin_id, dest_id, edge->properties, true);
    GraphToGrpc::parse_edge(res_edge, response->mutable_edge());
    return Status::OK;
}

Status ServiceImplementation::SearchNode(
    ServerContext *context,
    const SearchNodeReq *req,
    SearchNodeResponse *resp)
{
    AuthData data = AuthService::get_credentials(req->token());
    auto& manpl = manipulations[data.database_name];
    const NetworkNode req_node = req->node();
    if (req_node.id()) {
        manpl->getNodeById((long)req_node.id());
    }
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
    AuthData data = AuthService::get_credentials(req->token());
    auto& manpl = manipulations[data.database_name];
    
    return Status::OK;
}

Status ServiceImplementation::CreateRelation(
    ServerContext *ctx,
    const CreateRelationReq *req,
    CreateRelationResponse *response
) {
    auto source = req->source();
    auto destination = req->destination();
    auto attrs = req->rel_attrs();
    Edge* edge = new Edge();
    edge->properties["prop"] = "Shida";
    GraphToGrpc::parse_edge(edge, response->mutable_edge());
    return Status::OK;
}

ServiceImplementation::ServiceImplementation() {

}

ServiceImplementation::~ServiceImplementation() {

}