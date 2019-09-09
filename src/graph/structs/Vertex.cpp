#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Edge.h"
#include"Node.h"
using namespace std;

class VertexSerializable: Serializable {
	list<int> edgesIdList;
	int node;
};

class Vertex {
public:
	Node node;
	list<Edge> edgesList;
	VertexSerializable getSerializable() {

	}
};