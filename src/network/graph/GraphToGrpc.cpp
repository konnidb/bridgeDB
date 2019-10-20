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
#include "GraphToGrpc.h"

using namespace std;
using network::NetworkNode;
using network::NetworkEdge;

GraphToGrpc::GraphToGrpc(){};
NetworkNode GraphToGrpc::parse_node(Node* node) {
    NetworkNode n;
    auto fields = n.mutable_fields();
    auto props = node->properties;
    for_each(props.begin(), props.end(), [fields](pair<string, string> element) {
        auto key = element.first;
        // auto value = element.second;
        // (*fields)[key]=value;
        cout << key;
    });
    return n;
};

vector<NetworkNode*> GraphToGrpc::parse_node_vector(vector<Node*> nodes) {

};

static NetworkNode* parse_node_array(Node* nodes) {

};

GraphToGrpc::~GraphToGrpc(){};
