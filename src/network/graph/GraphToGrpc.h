#pragma once
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

using namespace std;
using network::NetworkNode;
using network::NetworkEdge;

class GraphToGrpc
{
private:
    
public:
    GraphToGrpc();
    static NetworkNode parse_node(Node* node, NetworkNode*);
    static NetworkEdge parse_edge(Edge* edge, NetworkEdge*);

    static vector<NetworkNode*> parse_node_vector(vector<Node*> nodes);
    static NetworkNode* parse_node_array(Node* nodes);
    static vector<NetworkEdge*> parse_edge_vector(vector<Edge*> edges);
    static NetworkEdge* parse_edge_array(Edge* edges);

    ~GraphToGrpc();
};
