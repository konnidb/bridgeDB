#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
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
#include "src/graph/structs/Vertex.h"
#include "src/graph/operations/Manipulation.h"
#include "src/graph/utils/Comparison.h"
#include "src/graph/structs/Database.h"
#include "graph/DBHandler.h"
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

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
using network::DeleteNodeReq;
using network::DeleteNodeResponse;
using network::DeleteEdgeReq;
using network::DeleteEdgeResponse;
using network::NetworkGraphRequest;
using network::NetworkGraphResponse;

Status ServiceImplementation::GetGraph(
    ServerContext* ctx,
    const NetworkGraphRequest* req,
    NetworkGraphResponse* resp
) {
    try {
        string token = req->token();
        AuthData data = AuthService::get_auth_data(token);
        Manipulation *manpl = DBHandler::loadDatabase(data.database_name, data.graph_name);
        vector<Node*> nodes = manpl->graph->getNodeVector();
        vector<Edge*> edges = manpl->graph->getEdgeVector();
        cout << "[ServiceImplementation] Nodes len: " << nodes.size() << " Edges len: " << edges.size() << endl;
        vector<NetworkNode> respNodesVector = GraphToGrpc::parse_node_vector(nodes);
        vector<NetworkEdge> respEdgesVector = GraphToGrpc::parse_edge_vector(edges);
        // manpl->graph->getNodeVector()
        *resp->mutable_nodes() = { respNodesVector.begin(), respNodesVector.end() };
        *resp->mutable_edges() = { respEdgesVector.begin(), respEdgesVector.end() };

        // Vertex vertex;
        // vector<Vertex*> vertexs = manpl->getVertexes(vertex);
        // for (auto& v: vertexs) {}
    } catch (exception& e) {
        return Status(StatusCode::ABORTED, e.what());
    }
    
    return Status::OK;
}

Status ServiceImplementation::CreateSession(
    ServerContext *context,
    const SessionRequest *request,
    Session *response)
{
    AuthCredentials rq_credentials;
    
    rq_credentials.username = request->username();
    rq_credentials.password = request->password();
    rq_credentials.database = request->database();
    rq_credentials.graph = request->graph();
    if (AuthService::validate_credentials(rq_credentials)) {
        cout << "Inside if" << endl;
        string token = AuthService::generate_token(rq_credentials);
        string* tkn = response->mutable_token();
        AuthData data = AuthService::get_auth_data(token);
        cout << "AuthData generated" << endl;
        cout << "[ServiceImplementation] Retrieving database from CreateSession" << endl;
        auto db = Database::getDatabase(rq_credentials.database);
        cout << "[ServiceImplementation] Database retrieved" << endl;
        auto graph = Graph::getGraph(rq_credentials.database, rq_credentials.graph);
        cout << "Graph aquired" << endl;
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
    try {
        string token = (string)query->token();
        AuthData authData = AuthService::get_auth_data(token);
        auto db = Database::getDatabase(authData.database_name);
        db->cfg->storeConfigFile();
        cout << "[ServiceImplementation] Created Config File" << endl;
    } catch(exception& e) {
        return Status(StatusCode::ABORTED, "Error creating config file");
    }
    
    return Status::OK;
};

Status ServiceImplementation::DeleteNode(
    ServerContext* ctx,
    const DeleteNodeReq* req,
    DeleteNodeResponse* resp
) {
    try {
        string token = req->token();
        AuthData data = AuthService::get_auth_data(token);
        Manipulation* manpl = DBHandler::loadDatabase(data.database_name, data.graph_name);
        long deletedId = (long)req->nodeid();
        Node* deleted = manpl->getNodeById(deletedId);
        GraphToGrpc::parse_node(deleted, resp->mutable_node());
        manpl->deleteNode(deletedId);
        manpl->graph->storeVertexMap();
    } catch (exception& e) {
        return Status(StatusCode::ABORTED, e.what());
    }
    return Status::OK;
}

Status ServiceImplementation::DeleteEdge(
    ServerContext* ctx,
    const DeleteEdgeReq* req,
    DeleteEdgeResponse* resp
) {
    return Status::OK;
}

Status ServiceImplementation::CreateNode(
    ServerContext *context,
    const CreateNodeReq *req,
    CreateNodeResponse *response)
{
    AuthData data = AuthService::get_auth_data(req->token());
    Manipulation* manpl = DBHandler::loadDatabase(data.database_name, data.graph_name);

    cout << "CREATING NODE";
    Node* node = new Node();
    NetworkNode req_node = (NetworkNode)req->node();
    NetworkNode* res_node = response->mutable_node();
    GrpcToGraph::parse_node(&req_node, node);
    cout << "About to create node" << endl;
    Node* stored_node = manpl->createNode(node->properties);
    manpl->graph->storeVertexMap();
    cout << "Stored nodeID: " << stored_node->id << endl;
    cout << "Node created" << endl;
    GraphToGrpc::parse_node(stored_node, res_node);

    return Status::OK;
}

Status ServiceImplementation::CreateEdge(
    ServerContext *contest,
    const CreateEdgeReq *req,
    CreateEdgeResponse *response)
{
    try {
        AuthData data = AuthService::get_auth_data(req->token());
        Manipulation* manpl = DBHandler::loadDatabase(data.database_name, data.graph_name);
        cout << "CREATING EDGE" << endl;
        NetworkEdge nt_req_edge = (NetworkEdge)req->edge();
        Edge* edge = new Edge();
        cout << "[ServiceImplementation] new edge created" << endl;
        GrpcToGraph::parse_edge(&nt_req_edge, edge);
        NetworkNode nt_rq_or = (NetworkNode)nt_req_edge.origin();
        NetworkNode nt_rq_dst = (NetworkNode)nt_req_edge.destination();
        cout << "[ServiceImplementation] parsed nodes and edge" << endl;
        long origin_id = (long)(nt_rq_or.id());
        long dest_id = (long)(nt_rq_dst.id());
        Node* or_node = manpl->getNodeById(origin_id);
        Node* dest_node = manpl->getNodeById(dest_id);
        cout << "[ServiceImplementation] Nodes retreived from engine" << endl;
        cout << "[ServiceImplementation] about te create edge" << endl;
        Edge* res_edge = manpl->createEdge(origin_id, dest_id, edge->properties, true);
        cout << "[ServiceImplementation] Edge Created!" << endl;
        GraphToGrpc::parse_edge(res_edge, response->mutable_edge());
        cout << "[ServiceImplementation] About to store vertex map" << endl;
        manpl->graph->storeVertexMap();
        cout << "[ServiceImplementation] Vertex map stored" << endl;
    } catch(exception& e) {
        return Status(StatusCode::ABORTED, e.what());
    }
    return Status::OK;
}

Status ServiceImplementation::SearchNode(
    ServerContext *context,
    const SearchNodeReq *req,
    SearchNodeResponse *resp)
{
    try {
        AuthData data = AuthService::get_auth_data(req->token());
        Manipulation* manpl = DBHandler::loadDatabase(data.database_name, data.graph_name);
        cout << "Manpl aquired" << endl;
        NetworkNode req_node = (NetworkNode)req->node();
        if (req_node.id()) {
            Node* res_node = manpl->getNodeById((long)req_node.id());
            cout << res_node->id << endl;
            NetworkNode* resNode = new NetworkNode();
            GraphToGrpc::parse_node(res_node, resNode);
            resp->mutable_nodes()->AddAllocated(resNode);
        } else {
            cout << "[ServiceImplementation] Not id in request" << endl;
            Node* tmpNode = new Node();
            cout << "[ServiceImplementation] Parsing node..." << endl;
            GrpcToGraph::parse_node(&req_node, tmpNode);
            cout << "[ServiceImplementation] Node parsed: " << tmpNode->id << endl;
            cout << "[ServiceImplementation] Aquiring vector" << endl;
            vector<Node*> nodes = manpl->getNodes(*tmpNode);
            cout << "[ServiceImplementation] Vector aquired: " << nodes.size() << endl;
            cout << "[ServiceImplementation] Parsing vector "<< endl;
            auto respNodes = GraphToGrpc::parse_node_vector(nodes);
            cout << "[ServiceImplementation] Vector parsed " << respNodes.size() << endl;
            *resp->mutable_nodes() = { respNodes.begin(), respNodes.end() };

        }
    } catch(exception& e) {
        return Status(StatusCode::NOT_FOUND, "NO ITEMS FOUND");
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
    AuthData data = AuthService::get_auth_data(req->token());
    Manipulation* manpl = DBHandler::loadDatabase(data.database_name, data.graph_name);
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