#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "src/graph/structs/Graph.h"
#include "src/graph/structs/Edge.h"
#include "src/graph/structs/Vertex.h"
#include "src/graph/structs/Node.h"
#include "network.grpc.pb.h"
#include "network.pb.h"
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
    static NetworkNode parse_node(Node* node) {
        NetworkNode n;
        auto fields = *(n.mutable_fields());
        auto props = node->properties;
        for_each(props.begin(), props.end(), [](pair<string, string> element) {
            auto key = element.first;
            auto value = element.second;
            *(n.mutable_fields())[key] = value;
        });
        
        n.mutable_fields();
        
    };

    static vector<NetworkNode*> parse_node_vector(vector<Node*> nodes) {

    };
    
    static NetworkNode* parse_node_array(Node* nodes) {

    }

    ~GraphToGrpc();
};

GraphToGrpc::GraphToGrpc()
{
}

GraphToGrpc::~GraphToGrpc()
{
}
