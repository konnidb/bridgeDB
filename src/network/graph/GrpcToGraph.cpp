#include <string>
#include <vector>
#include "GrpcToGraph.h"
#include "src/graph/structs/Edge.h"
#include "src/graph/structs/Node.h"
#include "src/graph/structs/Graph.h"
#include "../network.pb.h"
#include "../network.grpc.pb.h"

using network::NetworkEdge;
using network::NetworkGraph;
using network::NetworkNode;

using namespace std;

GrpcToGraph::GrpcToGraph()
{
};

Edge GrpcToGraph::parse_edge(NetworkEdge *n, Edge * edge){
    auto fields = *n->mutable_fields();
    auto props = &(edge->properties);
    for_each(fields.begin(), fields.end(), [props](pair<string, string> element) {
        auto key = element.first;
        auto value = element.second;
        (*props)[key] = value;
    });
    return *edge;
};

vector<Edge *> GrpcToGraph::parse_edge_vector(vector<NetworkEdge *>n_edges){
    vector<Edge*>* edges = new vector<Edge*>();
    for_each(n_edges.begin(), n_edges.end(), [edges](NetworkEdge* n_edge) {
        Edge* edge = new Edge();
        parse_edge(n_edge, edge);
        edges->push_back(edge);
    });
    return *edges;
};

Node *GrpcToGraph::parse_node(NetworkNode* n, Node *node){
    auto fields = *n->mutable_fields();
    auto props = &(node->properties);
    node->id = n->id();
    for_each(fields.begin(), fields.end(), [props](pair<string, string> element) {
        auto key = element.first;
        auto value = element.second;
        cout << key << ":" << value << endl;
        (*props)[key] = value;
    });
    return node;
};

vector<Node *> GrpcToGraph::parse_node_vector(vector<NetworkNode *>n_nodes){
    vector<Node*>* nodes = new vector<Node*>();
    for_each(n_nodes.begin(), n_nodes.end(), [nodes](NetworkNode* n_node) {
        Node* node = new Node();
        parse_node(n_node, node);
        nodes->push_back(node);
    });
    return *nodes;
};

void GrpcToGraph::parse_graph(NetworkGraph *, Graph *){

};

GrpcToGraph::~GrpcToGraph()
{
};
