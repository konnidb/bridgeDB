#pragma once
#include<iostream>
//#include<unordered_map>
#include"..\utils\Serializable.h"
#include"..\structs\Schema.cpp"
using namespace std;

class SerializableNode : public Serializable {
public:
	int schemaId;
	SerializableNode();
	void load();
	void store();
};

class Node {
public:
	Schema * schema;
	int id;
	unordered_map<string, string> properties;
	Node();
	SerializableNode getSerializable();
};