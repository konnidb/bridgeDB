#pragma once
#include<iostream>
#include<unordered_map>
#include"Node.h"
#include"Schema.cpp"
#include"..\utils\Serializable.h"
using namespace std;

class SerializableEdge : public Serializable {
public:
	int id;
	int schemaId;
	int originNode;
	int targetNode;
	SerializableEdge();
	void load();
	void store();
};

class Edge {
public:
	Schema * schema;
	int id;
	unordered_map<string, string> properties;
	Node * originNode;
	Node * targetNode;
	SerializableEdge getSerializable();
};