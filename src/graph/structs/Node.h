#pragma once
#include<iostream>
//#include<unordered_map>
#include"..\utils\Serializable.h"
#include"..\structs\Schema.h"
using namespace std;

class SerializableNode : public Serializable {
public:
	int schemaId;
	SerializableNode();
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};

class Node : public Element {
public:
	Schema * schema;
	int id;
	unordered_map<string, string> properties;
	Serializable* getSerializable(string path);
	Node();
	Node(int id, unordered_map<string, string> properties);
	Node(int id);
	Node(SerializableNode serializable);
	static bool compareNodes(Node* node1, Node* node2);
};