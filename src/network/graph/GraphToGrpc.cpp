#include <iostream>
#include <string>
#include <vector>
#include "src/graph/structs/Graph.h"
#include "src/graph/structs/Edge.h"
#include "src/graph/structs/Vertex.h"
#include "src/graph/structs/Node.h"
#include "src/network/network.grpc.pb.h"
#include "src/network/network.pb.h"
#include "grpc++/grpc++.h"
#include <unordered_map>
#include <string>
#include <algorithm>
#include "GraphToGrpc.h"
#include "src/graph/structs/Vertex.h"

using namespace std;
using network::NetworkNode;
using network::NetworkEdge;

GraphToGrpc::GraphToGrpc(){};

NetworkNode* GraphToGrpc::parse_vertex(Vertex* vertex, NetworkNode* n) {
    parse_node(vertex->node, n);
    Node* graphNode = vertex->node;
    vector<NetworkEdge> networkEdges = parse_edge_vector(vertex->edgesVector);
    *n->mutable_connections() = {networkEdges.begin(), networkEdges.end()};
}

NetworkNode GraphToGrpc::parse_node(Node* node, NetworkNode* n) {
    auto fields = n->mutable_fields();
    auto props = node->properties;
    n->set_id(node->id);
    for_each(props.begin(), props.end(), [fields](pair<string, string> element) {
        auto key = element.first;
        cout<<key<<endl;
        auto value = element.second;
        (*fields)[key]=value;
        cout << key;
    });
    return *n;
};

NetworkEdge GraphToGrpc::parse_edge(Edge* edge, NetworkEdge* e) {
    auto fields = e->mutable_fields();
    auto props = edge->properties;
    e->set_label(edge->label);
    for_each(props.begin(), props.end(), [fields](pair<string, string> element) {
        auto key = element.first;
        auto value = element.second;
        (*fields)[key] = value;
    });
    parse_node(edge->originNode, e->mutable_origin());
    parse_node(edge->targetNode, e->mutable_destination());
    return *e;
}

vector<NetworkNode> GraphToGrpc::parse_node_vector(vector<Node*> nodes) {
    vector<NetworkNode> *n_nodes = new vector<NetworkNode>();
    for_each(nodes.begin(), nodes.end(), [n_nodes](Node* node) {
        NetworkNode* n_node = new NetworkNode();
        parse_node(node, n_node);
        n_nodes->push_back(*n_node);
    });
    return *n_nodes;
};

vector<NetworkEdge> GraphToGrpc::parse_edge_vector(vector<Edge*> edges) {
    vector<NetworkEdge> *n_edges = new vector<NetworkEdge>();
    for_each(edges.begin(), edges.end(), [n_edges](Edge* edge) {
        NetworkEdge* n_edge = new NetworkEdge();
        parse_edge(edge, n_edge);
        n_edges->push_back(*n_edge);
    });
    return *n_edges;
};

static NetworkNode* parse_node_array(Node* nodes) {

};

GraphToGrpc::~GraphToGrpc(){};
