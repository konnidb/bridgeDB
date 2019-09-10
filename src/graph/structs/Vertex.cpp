#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Edge.h"
#include"Node.h"
using namespace std;

class VertexSerializable: Serializable {
	vector<int> edgesIdVector;
	int node;
};

class Vertex {
public:
	Node * node;
	vector<Edge *> edgesVector;
	VertexSerializable getSerializable() {

	}
};