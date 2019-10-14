#pragma once
#include<iostream>
//#include<unordered_map>
#include"..\utils\Serializable.h"
#include"Schema.h"
using namespace std;

class SerializableNode : public Serializable {
public:
	long schemaId;
	SerializableNode();
	~SerializableNode();
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};

class Node : public Element {
public:
	Schema * schema;
	long id;
	unordered_map<string, string> properties;
	Serializable* getSerializable(string path);
	Node();
	~Node();
	Node(long id, unordered_map<string, string> properties);
	Node(long id);
	Node(SerializableNode serializable);
	static bool compareNodes(Node* node1, Node* node2);
};