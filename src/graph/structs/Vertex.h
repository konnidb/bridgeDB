#pragma once
#include<iostream>
#include"..\utils\Serializable.h"
#include"Edge.h"
#include"Node.h"
using namespace std;

class SerializableVertex : public Serializable {
public:
	vector<int> edgesIdVector;
	int node;
	SerializableVertex();
	void load(ifstream* streamObj);
	void store(ofstream* streamObj);
};

class Vertex : public Element {
public:
	int id;
	Node * node;
	vector<Edge *> edgesVector;
	Serializable* getSerializable(string path);
	Vertex();
	Vertex(int id, Node * node);
};

