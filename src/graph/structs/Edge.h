#pragma once
#include<iostream>
#include"Node.h"
#include"Schema.cpp"
#include"..\utils\Serializable.h"
using namespace std;

class SerializableEdge : public Serializable {
public:
	int id;
	int originNode;
	int targetNode;
	SerializableEdge();
};

class Edge {
public:
	Schema * schema;
	int id;
	unordered_map<string, string> properties;
	Node originNode;
	Node targetNode;
	SerializableEdge getSerializable();
};