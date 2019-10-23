#include <string>
#include <vector>
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

Edge GrpcToGraph::parse_edge(NetworkEdge *, Edge *){

};

vector<Edge *> GrpcToGraph::parse_edge_vector(vector<NetworkEdge *>){

};

Node *GrpcToGraph::parse_node(NetworkNode *, Node *){

};

vector<Node *> GrpcToGraph::parse_node_vector(vector<NetworkNode *>){

};

void GrpcToGraph::parse_graph(NetworkGraph *, Graph *){

};

GrpcToGraph::~GrpcToGraph()
{
};
