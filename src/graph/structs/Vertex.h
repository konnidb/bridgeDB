#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Edge.h"
#include"Node.h"
using namespace std;

class VertexSerializable : public Serializable {
public:
	vector<int> edgesIdVector;
	int node;
	VertexSerializable();
};

class Vertex {
public:
	int id;
	Node * node;
	vector<Edge *> edgesVector;
	VertexSerializable getSerializable();
};

