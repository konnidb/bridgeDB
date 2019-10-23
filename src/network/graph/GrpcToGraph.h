#pragma once
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

class GrpcToGraph
{
private:
public:
    GrpcToGraph();
    static Edge parse_edge(NetworkEdge *, Edge *);
    static vector<Edge *> parse_edge_vector(vector<NetworkEdge *>);
    static Node *parse_node(NetworkNode *, Node *);
    static vector<Node *> parse_node_vector(vector<NetworkNode *>);
    static void parse_graph(NetworkGraph *, Graph *);
    ~GrpcToGraph();
    ;
};
