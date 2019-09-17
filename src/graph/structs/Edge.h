#pragma once
#include<iostream>
//#include<unordered_map>
#include"Node.h"
#include"Schema.h"
#include"..\utils\Serializable.h"
using namespace std;

class SerializableEdge : public Serializable {
public:
	int id;
	int schemaId;
	int originNode;
	int targetNode;
	SerializableEdge();
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};

class Edge : public Element {
public:
	Schema * schema;
	int id;
	unordered_map<string, string> properties;
	Node * originNode;
	Node * targetNode;
	Serializable* getSerializable(string path);
	Edge();
	Edge(int id, unordered_map<string, string> properties);
	Edge(int id, unordered_map<string, string> properties, Node * originNode, Node * targetNode);
	Edge(SerializableEdge serializable);
	static bool compareEdges(Edge* edge1, Edge* edge2);
};