#include<iostream>
#include<unordered_map>
#include<string>
#include"..\..\utils\LogHandler.cpp"
#include"..\utils\Serializable.cpp"
#include"Node.cpp"
using namespace std;

class EdgeSerializable : Serializable {
public:
	int originNode;
	int targetNode;
	EdgeSerializable() : objType(EDGE) {}
};

class Edge {
public:
	Node * originNode;
	Node * targetNode;
	EdgeSerializable getSerializable() {}
};