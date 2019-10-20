#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "src/graph/structs/Graph.cpp"
#include "src/graph/structs/Edge.cpp"
#include "src/graph/structs/Vertex.cpp"
#include "src/graph/structs/Node.cpp"
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
    static NetworkNode parse_node(Node* node);

    static vector<NetworkNode*> parse_node_vector(vector<Node*> nodes);
    
    static NetworkNode* parse_node_array(Node* nodes);

    ~GraphToGrpc();
};
