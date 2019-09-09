#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
//#include"..\structs\Schema.cpp"
using namespace std;

class SerializableNode : public Serializable {
public:
	SerializableNode();
};

class Node {
public:
	//Schema * schema;
	int id;
	unordered_map<string, string> properties;
	Node();
	SerializableNode getSerializable();
};