#include <iostream>
#include <string>
#include "GraphToGrpc.cpp"
#include "src/network/network.grpc.pb.cc"
#include "src/network/network.pb.cc"
using namespace std;

int main(int argc, char const *argv[])
{
    Node graphNode;
    graphNode.id=1;
    unordered_map<string, string> props;
    props["prop1"] = "here i am";
    props["prop2"] = "rock u like a urracane";
    graphNode.properties = props;
    GraphToGrpc::parse_node(&graphNode);
    /* code */
    return 0;
}
