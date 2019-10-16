#pragma once
#include<iostream>
//#include<unordered_map>
#include"Node.h"
#include"Schema.h"
#include"..\utils\Serializable.h"
using namespace std;

class SerializableEdge : public Serializable {
public:
	long id;
	long schemaId;
	long originNode;
	long targetNode;
	SerializableEdge();
	~SerializableEdge();
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};

class Edge : public Element {
public:
	Schema * schema;
	long id;
	unordered_map<string, string> properties;
	Node * originNode;
	Node * targetNode;
	Serializable* getSerializable(string path);
	Edge();
	~Edge();
	Edge(long id);
	Edge(long id, unordered_map<string, string> properties);
	Edge(long id, unordered_map<string, string> properties, Node * originNode, Node * targetNode);
	Edge(SerializableEdge serializable);
	static bool compareEdges(Edge* edge1, Edge* edge2);
};